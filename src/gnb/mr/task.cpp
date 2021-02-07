//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "task.hpp"
#include "rls.hpp"
#include <gnb/nts.hpp>
#include <utils/constants.hpp>
#include <utils/libc_error.hpp>

static const int TIMER_ID_RLS_HEARTBEAT = 1;

namespace nr::gnb
{

GnbMrTask::GnbMrTask(TaskBase *base) : m_base{base}, m_udpTask{}, m_rlsEntity{}, m_ueMap{}
{
    m_logger = m_base->logBase->makeUniqueLogger("mr");
}

void GnbMrTask::onStart()
{
    m_rlsEntity = new GnbRls(m_base->config->name, m_base->logBase->makeUniqueLogger("rls"), this);

    try
    {
        m_udpTask = new udp::UdpServerTask(m_base->config->portalIp, cons::PortalPort, this);
        m_udpTask->start();
    }
    catch (const LibError &e)
    {
        m_logger->err("MR failure [%s]", e.what());
        quit();
        return;
    }

    setTimer(TIMER_ID_RLS_HEARTBEAT, rls::Constants::HB_PERIOD_UE_TO_GNB);
}

void GnbMrTask::onLoop()
{
    NtsMessage *msg = take();
    if (!msg)
        return;

    switch (msg->msgType)
    {
    case NtsMessageType::GNB_GTP_TO_MR: {
        auto *w = dynamic_cast<NwGtpToMr *>(msg);
        switch (w->present)
        {
        case NwGtpToMr::DATA_PDU_DELIVERY: {
            OctetString stream{};
            stream.appendOctet4(static_cast<int>(w->pduSessionId));
            stream.append(w->data);

            m_rlsEntity->downlinkPayloadDelivery(w->ueId, rls::EPayloadType::DATA, std::move(stream));
            break;
        }
        }
        delete w;
        break;
    }
    case NtsMessageType::GNB_RRC_TO_MR: {
        auto *w = dynamic_cast<NwGnbRrcToMr *>(msg);
        switch (w->present)
        {
        case NwGnbRrcToMr::RRC_PDU_DELIVERY: {
            OctetString stream{};
            stream.appendOctet(static_cast<int>(w->channel));
            stream.append(w->pdu);

            m_rlsEntity->downlinkPayloadDelivery(w->ueId, rls::EPayloadType::RRC, std::move(stream));
            break;
        }
        }
        delete w;
        break;
    }
    case NtsMessageType::TIMER_EXPIRED: {
        auto *w = dynamic_cast<NwTimerExpired *>(msg);
        if (w->timerId == TIMER_ID_RLS_HEARTBEAT)
        {
            setTimer(TIMER_ID_RLS_HEARTBEAT, rls::Constants::HB_PERIOD_GNB_TO_UE);
            m_rlsEntity->onHeartbeat();
        }
        delete w;
        break;
    }
    case NtsMessageType::UDP_SERVER_RECEIVE: {
        auto *w = dynamic_cast<udp::NwUdpServerReceive *>(msg);
        m_rlsEntity->onReceive(w->fromAddress, w->packet);
        delete w;
        break;
    }
    case NtsMessageType::GNB_RLS_UE_CONNECTED: {
        auto *w = dynamic_cast<NwUeConnected *>(msg);
        onUeConnected(w->ue, w->name);
        delete w;
        break;
    }
    case NtsMessageType::GNB_RLS_UE_RELEASED: {
        auto *w = dynamic_cast<NwUeReleased *>(msg);
        onUeReleased(w->ue, w->cause);
        delete w;
        break;
    }
    case NtsMessageType::GNB_RLS_UPLINK_PAYLOAD: {
        auto *w = dynamic_cast<NwUplinkPayload *>(msg);
        receiveUplinkPayload(w->ue, w->type, std::move(w->payload));
        delete w;
        break;
    }
    case NtsMessageType::GNB_RLS_SEND_PDU: {
        auto *w = dynamic_cast<NwRlsSendPdu *>(msg);
        m_udpTask->send(w->address, w->pdu);
        delete w;
        break;
    }
    case NtsMessageType::GNB_MR_N1_IS_READY: {
        m_rlsEntity->setN1IsReady(true);
        delete msg;
        break;
    }
    default:
        m_logger->unhandledNts(msg);
        delete msg;
        break;
    }
}

void GnbMrTask::onQuit()
{
    delete m_rlsEntity;

    if (m_udpTask != nullptr)
        m_udpTask->quit();
    delete m_udpTask;
}

void GnbMrTask::onUeConnected(int ue, const std::string &name)
{
    m_ueMap[ue] = {};
    m_ueMap[ue].ueId = ue;
    m_ueMap[ue].name = name;

    m_logger->info("New UE connected to gNB. Total number of UEs is now: %d", m_ueMap.size());
}

void GnbMrTask::onUeReleased(int ue, rls::ECause cause)
{
    m_ueMap.erase(ue);
    m_logger->info("A UE disconnected from gNB. Total number of UEs is now: %d", m_ueMap.size());
}

void GnbMrTask::receiveUplinkPayload(int ue, rls::EPayloadType type, OctetString &&payload)
{
    if (type == rls::EPayloadType::RRC)
    {
        auto *nw = new NwGnbMrToRrc(NwGnbMrToRrc::RRC_PDU_DELIVERY);
        nw->ueId = ue;
        nw->channel = static_cast<rrc::RrcChannel>(payload.getI(0));
        nw->pdu = payload.subCopy(1);
        m_base->rrcTask->push(nw);
    }
    else if (type == rls::EPayloadType::DATA)
    {
        int psi = payload.get4I(0);
        OctetString dataPayload = payload.subCopy(4);

        auto *w = new NwMrToGtp(NwMrToGtp::UPLINK_DELIVERY);
        w->ueId = ue;
        w->pduSessionId = psi;
        w->data = std::move(dataPayload);
        m_base->gtpTask->push(w);
    }
}

} // namespace nr::gnb
