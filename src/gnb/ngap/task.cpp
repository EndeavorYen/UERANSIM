//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
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
        m_base->sctpTask->push(new NwSctpConnectionRequest(amfCtx.second->ctxId, m_base->config->ngapIp, 0,
                                                           amfCtx.second->address, amfCtx.second->port,
                                                           sctp::PayloadProtocolId::NGAP, this));
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
    case NtsMessageType::SCTP_ASSOCIATION_SETUP: {
        handleAssociationSetup(dynamic_cast<NwSctpAssociationSetup *>(msg));
        break;
    }
    case NtsMessageType::SCTP_CLIENT_RECEIVE: {
        handleSctpMessage(dynamic_cast<NwSctpClientReceive *>(msg));
        break;
    }
    case NtsMessageType::NGAP_INITIAL_NAS_DELIVERY: {
        auto *w = dynamic_cast<NwInitialNasDelivery *>(msg);
        handleInitialNasTransport(w->ueId, w->nasPdu, w->rrcEstablishmentCause);
        delete w;
        break;
    }
    case NtsMessageType::NGAP_UPLINK_NAS_DELIVERY: {
        auto *w = dynamic_cast<NwUplinkNasDelivery *>(msg);
        handleUplinkNasTransport(w->ueId, w->nasPdu);
        delete w;
        break;
    }
    default: {
        m_logger->err("Unhandled NTS message received with type %d", (int)msg->msgType);
        delete msg;
        break;
    }
    }
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
