//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "task.hpp"
#include <ue/nts.hpp>
#include <utils/common.hpp>
#include <utils/constants.hpp>

static const int TIMER_ID_RLS_WAITING_TIMER = 1;
static const int TIMER_ID_RLS_HEARTBEAT = 2;
static const int PLMN_SEARCH_FAILED_PRINT_THRESHOLD = 10000;

namespace nr::ue
{

ue::UeMrTask::UeMrTask(TaskBase *base) : m_base{base}, m_udpTask{}, m_rlsEntity{}, m_lastPlmnSearchFailurePrinted{}
{
    m_logger = m_base->logBase->makeUniqueLogger(m_base->config->getLoggerPrefix() + "mr");
}

void UeMrTask::onStart()
{
    m_udpTask = new udp::UdpServerTask(this);

    std::vector<InetAddress> gnbSearchList{};
    for (auto &ip : m_base->config->gnbSearchList)
        gnbSearchList.emplace_back(ip, cons::PortalPort);

    m_rlsEntity = new UeRls(m_base->config->getNodeName(), gnbSearchList,
                            m_base->logBase->makeUniqueLogger(m_base->config->getLoggerPrefix() + "rls"), this);

    m_udpTask->start();

    setTimer(TIMER_ID_RLS_HEARTBEAT, rls::Constants::HB_PERIOD_UE_TO_GNB);
}

void UeMrTask::onQuit()
{
    delete m_rlsEntity;

    m_udpTask->quit();
    delete m_udpTask;
}

void UeMrTask::onLoop()
{
    NtsMessage *msg = take();
    if (!msg)
        return;

    switch (msg->msgType)
    {
    case NtsMessageType::UE_MR_TO_MR: {
        auto *w = dynamic_cast<NwUeMrToMr *>(msg);
        switch (w->present)
        {
        case NwUeMrToMr::RLS_CONNECTED: {
            auto tw = new NwUeMrToRrc(NwUeMrToRrc::PLMN_SEARCH_RESPONSE);
            tw->gnbName = std::move(w->gnbName);
            m_base->rrcTask->push(tw);
            break;
        }
        case NwUeMrToMr::RLS_RELEASED: {
            m_logger->warn("UE disconnected from gNB, RLS released [%s]", rls::CauseToString(w->cause));
            break;
        }
        case NwUeMrToMr::RLS_SEARCH_FAILURE: {
            long current = utils::CurrentTimeMillis();
            if (current - m_lastPlmnSearchFailurePrinted > PLMN_SEARCH_FAILED_PRINT_THRESHOLD)
            {
                m_logger->err("PLMN search failed [%s]", rls::CauseToString(w->cause));
                m_lastPlmnSearchFailurePrinted = current;
                m_base->rrcTask->push(new NwUeMrToRrc(NwUeMrToRrc::PLMN_SEARCH_FAILURE));
            }
            break;
        }
        case NwUeMrToMr::RLS_START_WAITING_TIMER: {
            setTimer(TIMER_ID_RLS_WAITING_TIMER, w->period);
            break;
        }
        case NwUeMrToMr::RLS_SEND_OVER_UDP: {
            m_udpTask->send(w->address, w->pdu);
            break;
        }
        case NwUeMrToMr::RLS_RECEIVE_OVER_UDP: {
            receiveDownlinkPayload(w->type, std::move(w->pdu));
            break;
        }
        }
        delete w;
        break;
    }
    case NtsMessageType::UE_RRC_TO_MR: {
        auto *w = dynamic_cast<NwUeRrcToMr *>(msg);
        switch (w->present)
        {
        case NwUeRrcToMr::PLMN_SEARCH_REQUEST: {
            m_rlsEntity->startGnbSearch();
            break;
        }
        }
        delete w;
        break;
    }
    case NtsMessageType::TIMER_EXPIRED: {
        auto *w = dynamic_cast<NwTimerExpired *>(msg);
        if (w->timerId == TIMER_ID_RLS_WAITING_TIMER)
        {
            m_rlsEntity->onWaitingTimerExpire();
        }
        else if (w->timerId == TIMER_ID_RLS_HEARTBEAT)
        {
            setTimer(TIMER_ID_RLS_HEARTBEAT, rls::Constants::HB_PERIOD_UE_TO_GNB);
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
    case NtsMessageType::UE_MR_UPLINK_RRC: {
        auto *w = dynamic_cast<NwUeUplinkRrc *>(msg);

        // Append channel information
        OctetString stream{};
        stream.appendOctet(static_cast<int>(w->channel));
        stream.append(w->rrcPdu);

        m_rlsEntity->onUplinkDelivery(rls::EPayloadType::RRC, std::move(stream));
        delete w;
        break;
    }
    case NtsMessageType::UE_MR_UPLINK_DATA: {
        auto *w = dynamic_cast<NwUeUplinkData *>(msg);

        // Append PDU session information
        OctetString stream{};
        stream.appendOctet4(w->psi);
        stream.append(w->data);

        m_rlsEntity->onUplinkDelivery(rls::EPayloadType::DATA, std::move(stream));
        delete w;
        break;
    }
    default:
        m_logger->err("Unhandled NTS message received with type [%d]", (int)msg->msgType);
        delete msg;
        break;
    }
}

void UeMrTask::receiveDownlinkPayload(rls::EPayloadType type, OctetString &&payload)
{
    if (type == rls::EPayloadType::RRC)
    {
        auto ch = static_cast<rrc::RrcChannel>(payload.getI(0));
        OctetString rrcPayload = payload.subCopy(1);
        m_base->rrcTask->push(new NwUeDownlinkRrc(ch, std::move(rrcPayload)));
    }
    else if (type == rls::EPayloadType::DATA)
    {
        int psi = payload.get4I(0);
        OctetString dataPayload = payload.subCopy(4);
        m_base->appTask->push(new NwUeDownlinkData(psi, std::move(dataPayload)));
    }
}

} // namespace nr::ue
