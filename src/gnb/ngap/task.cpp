//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "task.hpp"
#include <gnb/app/task.hpp>

#include <utils/common.hpp>

namespace nr::gnb
{

NgapTask::NgapTask(TaskBase *base) : m_base{base}, m_ueNgapIdCounter{}, m_waitingSctpClients{}, m_downlinkTeidCounter{}
{
    m_logger = base->logBase->makeUniqueLogger("ngap");
}

void NgapTask::onStart()
{
    for (auto &amfConfig : m_base->config->amfConfigs)
        createAmfContext(amfConfig);
    if (m_amfCtx.empty())
        m_logger->warn("No AMF configuration is provided");

    for (auto &amfCtx : m_amfCtx)
    {
        auto *msg = new NwGnbSctp(NwGnbSctp::CONNECTION_REQUEST);
        msg->clientId = amfCtx.second->ctxId;
        msg->localAddress = m_base->config->ngapIp;
        msg->localPort = 0;
        msg->remoteAddress = amfCtx.second->address;
        msg->remotePort = amfCtx.second->port;
        msg->ppid = sctp::PayloadProtocolId::NGAP;
        msg->associatedTask = this;
        m_base->sctpTask->push(msg);

        m_waitingSctpClients++;
    }
}

void NgapTask::onLoop()
{
    NtsMessage *msg = take();
    if (!msg)
        return;

    switch (msg->msgType)
    {
    case NtsMessageType::GNB_RRC_TO_NGAP: {
        auto *w = dynamic_cast<NwGnbRrcToNgap *>(msg);
        switch (w->present)
        {
        case NwGnbRrcToNgap::INITIAL_NAS_DELIVERY: {
            handleInitialNasTransport(w->ueId, w->pdu, w->rrcEstablishmentCause);
            break;
        }
        case NwGnbRrcToNgap::UPLINK_NAS_DELIVERY: {
            handleUplinkNasTransport(w->ueId, w->pdu);
            break;
        }
        }
        break;
    }
    case NtsMessageType::GNB_SCTP: {
        auto *w = dynamic_cast<NwGnbSctp *>(msg);
        switch (w->present)
        {
        case NwGnbSctp::ASSOCIATION_SETUP:
            handleAssociationSetup(w->clientId, w->associationId, w->inStreams, w->outStreams);
            break;
        case NwGnbSctp::RECEIVE_MESSAGE:
            handleSctpMessage(w->clientId, w->stream, w->buffer, w->length);
            break;
        default:
            m_logger->err("Unhandled NTS message received with type %d", (int)msg->msgType);
            break;
        }
        break;
    }
    default: {
        m_logger->err("Unhandled NTS message received with type %d", (int)msg->msgType);
        break;
    }
    }

    delete msg;
}

void NgapTask::onQuit()
{
    for (auto &i : m_ueCtx)
        delete i.second;
    for (auto &i : m_amfCtx)
        delete i.second;
    m_ueCtx.clear();
    m_amfCtx.clear();
}

} // namespace nr::gnb
