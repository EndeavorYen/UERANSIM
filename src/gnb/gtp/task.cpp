//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "task.hpp"

#include <asn/ngap/ASN_NGAP_QosFlowSetupRequestItem.h>
#include <gtp/encode.hpp>
#include <gtp/message.hpp>
#include <utils/constants.hpp>
#include <utils/libc_error.hpp>

namespace nr::gnb
{

GtpTask::GtpTask(TaskBase *base)
    : m_base{base}, m_udpServer{}, m_ueContexts{}, m_rateLimiter(std::make_unique<RateLimiter>()), m_pduSessions{}, m_sessionTree{}
{
    m_logger = m_base->logBase->makeUniqueLogger("gtp");
}

void GtpTask::onStart()
{
    try
    {
        m_udpServer = new udp::UdpServerTask(m_base->config->gtpIp, cons::GtpPort, this);
        m_udpServer->start();
    }
    catch (const LibError &e)
    {
        m_logger->err("GTP/UDP task could not be created. %s", e.what());
    }
}

void GtpTask::onQuit()
{
    m_udpServer->quit();
    delete m_udpServer;

    m_ueContexts.clear();
}

void GtpTask::onLoop()
{
    NtsMessage *msg = take();
    if (!msg)
        return;

    switch (msg->msgType)
    {
    case NtsMessageType::UDP_SERVER_RECEIVE:
        handleUdpReceive(dynamic_cast<udp::NwUdpServerReceive *>(msg));
        break;
    case NtsMessageType::GTP_UE_CONTEXT_UPDATE:
        handleUeContextUpdate(dynamic_cast<NwUeContextUpdate *>(msg));
        break;
    case NtsMessageType::NGAP_PDU_SESSION_RESOURCE_CREATE:
        handleSessionCreate(dynamic_cast<NwPduSessionResourceCreate *>(msg));
        break;
    case NtsMessageType::GNB_MR_UPLINK_DATA:
        handleUplinkData(dynamic_cast<NwUplinkData *>(msg));
        break;
    default:
        m_logger->unhandledNts(msg);
        delete msg;
        break;
    }
}

void GtpTask::handleUeContextUpdate(NwUeContextUpdate *msg)
{
    if (!m_ueContexts.count(msg->ueId))
        m_ueContexts[msg->ueId] = std::make_unique<GtpUeContext>(msg->ueId);

    auto &ue = m_ueContexts[msg->ueId];
    ue->ueAmbr = msg->ueAmbr;

    updateAmbrForUe(ue->ueId);

    delete msg;
}

void GtpTask::handleSessionCreate(NwPduSessionResourceCreate *msg)
{
    PduSessionResource *session = msg->resource;
    if (!m_ueContexts.count(session->ueId))
    {
        m_logger->err("PDU session resource could not be created, UE context with ID[%d] not found", session->ueId);
        return;
    }

    uint64_t sessionInd = MakeSessionResInd(session->ueId, session->psi);
    m_pduSessions[sessionInd] = std::unique_ptr<PduSessionResource>(session);

    m_sessionTree.insert(sessionInd, session->downTunnel.teid);

    updateAmbrForUe(session->ueId);
    updateAmbrForSession(sessionInd);

    delete msg;
}

void GtpTask::handleUplinkData(NwUplinkData *msg)
{
    const uint8_t *data = msg->data.data();

    // ignore non IPv4 packets
    if ((data[0] >> 4 & 0xF) != 4)
    {
        delete msg;
        return;
    }

    uint64_t sessionInd = MakeSessionResInd(msg->ueId, msg->pduSessionId);

    if (!m_pduSessions.count(sessionInd))
    {
        m_logger->err("Uplink data failure, PDU session not found. UE: %d PSI: %d", msg->ueId, msg->pduSessionId);
        delete msg;
        return;
    }

    auto &pduSession = m_pduSessions[sessionInd];

    if (m_rateLimiter->allowUplinkPacket(sessionInd, static_cast<int64_t>(msg->data.length())))
    {
        gtp::GtpMessage gtp{};
        gtp.payload = std::move(msg->data);
        gtp.msgType = gtp::GtpMessage::MT_G_PDU;
        gtp.teid = pduSession->upTunnel.teid;

        auto ul = std::make_unique<gtp::UlPduSessionInformation>();
        // TODO: currently using first QSI
        ul->qfi = static_cast<int>(pduSession->qosFlows->list.array[0]->qosFlowIdentifier);

        auto cont = new gtp::PduSessionContainerExtHeader();
        cont->pduSessionInformation = std::move(ul);
        gtp.extHeaders.push_back(std::unique_ptr<gtp::GtpExtHeader>(cont));

        OctetString gtpPdu;
        if (!gtp::EncodeGtpMessage(gtp, gtpPdu))
            m_logger->err("Uplink data failure, GTP encoding failed");
        else
        {
            m_udpServer->send(InetAddress(pduSession->upTunnel.address, cons::GtpPort), gtpPdu);
        }
    }

    delete msg;
}

void GtpTask::handleUdpReceive(udp::NwUdpServerReceive *msg)
{
    OctetView buffer{msg->packet};
    auto *gtp = gtp::DecodeGtpMessage(buffer);

    auto sessionInd = m_sessionTree.findByDownTeid(gtp->teid);
    if (sessionInd == 0)
    {
        m_logger->err("TEID %d not found on GTP-U Downlink", gtp->teid);
        delete gtp;
        delete msg;
        return;
    }

    if (gtp->msgType != gtp::GtpMessage::MT_G_PDU)
    {
        m_logger->err("Unhandled GTP-U message type: %d", gtp->msgType);
        delete gtp;
        delete msg;
        return;
    }

    if (m_rateLimiter->allowDownlinkPacket(sessionInd, gtp->payload.length()))
        m_base->mrTask->push(new NwDownlinkData(GetUeId(sessionInd), GetPsi(sessionInd), std::move(gtp->payload)));

    delete gtp;
    delete msg;
}

void GtpTask::updateAmbrForUe(int ueId)
{
    if (!m_ueContexts.count(ueId))
        return;

    auto &ue = m_ueContexts[ueId];
    m_rateLimiter->updateUeUplinkLimit(ueId, ue->ueAmbr.ulAmbr);
    m_rateLimiter->updateUeDownlinkLimit(ueId, ue->ueAmbr.dlAmbr);
}

void GtpTask::updateAmbrForSession(uint64_t pduSession)
{
    if (!m_pduSessions.count(pduSession))
        return;

    auto &sess = m_pduSessions[pduSession];
    m_rateLimiter->updateSessionUplinkLimit(pduSession, sess->sessionAmbr.ulAmbr);
    m_rateLimiter->updateSessionDownlinkLimit(pduSession, sess->sessionAmbr.dlAmbr);
}

} // namespace nr::gnb
