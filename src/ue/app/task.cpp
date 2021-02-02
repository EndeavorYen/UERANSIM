//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "task.hpp"
#include <nas/utils.hpp>
#include <ue/tun/tun.hpp>
#include <utils/common.hpp>
#include <utils/constants.hpp>

namespace nr::ue
{

UeAppTask::UeAppTask(TaskBase *base) : m_base{base}, m_statusInfo{}, m_tunTasks{}
{
    m_logger = m_base->logBase->makeUniqueLogger(m_base->config->getLoggerPrefix() + "app");
}

void UeAppTask::onStart()
{
}

void UeAppTask::onQuit()
{
    for (auto &tunTask : m_tunTasks)
    {
        if (tunTask != nullptr)
        {
            tunTask->quit();
            delete tunTask;
            tunTask = nullptr;
        }
    }
}

void UeAppTask::onLoop()
{
    NtsMessage *msg = take();
    if (!msg)
        return;

    switch (msg->msgType)
    {
    case NtsMessageType::UE_STATUS_UPDATE: {
        receiveStatusUpdate(*dynamic_cast<NwUeStatusUpdate *>(msg));
        delete msg;
        break;
    }
    case NtsMessageType::UE_TUN_RECEIVE: {
        auto *w = dynamic_cast<NwTunReceive *>(msg);
        m_base->mrTask->push(new NwUeUplinkData(w->psi, std::move(w->data)));
        delete msg;
        break;
    }
    case NtsMessageType::UE_TUN_ERROR: {
        m_logger->err("TUN failure [%s]", dynamic_cast<NwTunError *>(msg)->error.c_str());
        delete msg;
        break;
    }
    case NtsMessageType::UE_MR_DOWNLINK_DATA: {
        auto *w = dynamic_cast<NwUeDownlinkData *>(msg);
        auto *tunTask = m_tunTasks[w->psi];
        if (tunTask)
            tunTask->push(w);
        else
            delete w;
        break;
    }
    default:
        m_logger->err("Unhandled NTS message received with type %d", (int)msg->msgType);
        delete msg;
        break;
    }
}

void UeAppTask::receiveStatusUpdate(NwUeStatusUpdate &msg)
{
    if (msg.what == NwUeStatusUpdate::CONNECTED_GNB)
    {
        if (msg.gnbName.length() > 0)
        {
            m_statusInfo.connectedGnb = std::move(msg.gnbName);
            m_statusInfo.isConnected = true;
        }
        else
        {
            m_statusInfo.connectedGnb = {};
            m_statusInfo.isConnected = false;
        }
    }
    else if (msg.what == NwUeStatusUpdate::MM_STATE)
    {
        m_statusInfo.mmState = msg.mmSubState;
    }
    else if (msg.what == NwUeStatusUpdate::RM_STATE)
    {
        m_statusInfo.rmState = msg.rmState;
    }
    else if (msg.what == NwUeStatusUpdate::CM_STATE)
    {
        m_statusInfo.cmState = msg.cmState;
    }
    else if (msg.what == NwUeStatusUpdate::SESSION_ESTABLISHMENT)
    {
        auto *session = msg.pduSession;

        UeStatusInfo::UePduSessionInfo sessionInfo{};
        sessionInfo.type = nas::utils::EnumToString(session->sessionType);
        if (session->pduAddress.has_value())
            sessionInfo.address = utils::OctetStringToIp(session->pduAddress->pduAddressInformation);

        m_statusInfo.pduSessions[session->id] = std::move(sessionInfo);

        setupTunInterface(session);
    }
}

void UeAppTask::setupTunInterface(const PduSession *pduSession)
{
    if (!utils::IsRoot())
    {
        m_logger->err("TUN interface could not be setup. Permission denied. Please run the UE with 'sudo'");
        return;
    }

    if (!pduSession->pduAddress.has_value())
    {
        m_logger->err("Connection could not setup. PDU address is missing.");
        return;
    }

    if (pduSession->pduAddress->sessionType != nas::EPduSessionType::IPV4 ||
        pduSession->sessionType != nas::EPduSessionType::IPV4)
    {
        m_logger->err("Connection could not setup. PDU session type is not supported.");
        return;
    }

    int psi = pduSession->id;
    if (psi == 0 || psi > 15)
    {
        m_logger->err("Connection could not setup. Invalid PSI.");
        return;
    }

    if (m_tunTasks[psi] != nullptr)
    {
        m_logger->err("Connection could not setup. TUN task for specified PSI is non-null.");
        return;
    }

    std::string error{}, allocatedName{};
    int fd = tun::TunAllocate(cons::TunNamePrefix, allocatedName, error);
    if (fd == 0 || error.length() > 0)
    {
        m_logger->err("TUN allocation failure [%s]", error.c_str());
        return;
    }

    std::string ipAddress = utils::OctetStringToIp(pduSession->pduAddress->pduAddressInformation);

    bool r = tun::TunConfigure(allocatedName, ipAddress, m_base->config->configureRouting, error);
    if (!r || error.length() > 0)
    {
        m_logger->err("TUN configuration failure [%s]", error.c_str());
        return;
    }

    auto *task = new TunTask(m_base, psi, fd);
    m_tunTasks[psi] = task;
    task->start();

    m_logger->info("Connection setup for PDU session[%d] is successful, TUN interface[%s, %s] is up.", pduSession->id,
                   allocatedName.c_str(), ipAddress.c_str());
}

} // namespace nr::ue
