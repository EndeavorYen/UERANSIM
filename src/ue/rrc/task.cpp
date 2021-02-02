//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "task.hpp"
#include <asn/rrc/ASN_RRC_RRCSetupRequest-IEs.h>
#include <asn/rrc/ASN_RRC_RRCSetupRequest.h>
#include <asn/rrc/ASN_RRC_ULInformationTransfer-IEs.h>
#include <asn/rrc/ASN_RRC_ULInformationTransfer.h>
#include <rrc/encode.hpp>
#include <utils/common.hpp>

namespace nr::ue
{

UeRrcTask::UeRrcTask(TaskBase *base) : m_base{base}
{
    m_logger = base->logBase->makeUniqueLogger(base->config->getLoggerPrefix() + "rrc");

    m_state = ERrcState::RRC_IDLE;
}

void UeRrcTask::onStart()
{
    m_logger->debug("RRC layer started");
}

void UeRrcTask::onQuit()
{
    // TODO
}

void UeRrcTask::onLoop()
{
    NtsMessage *msg = take();
    if (!msg)
        return;

    switch (msg->msgType)
    {
    case NtsMessageType::UE_MR_DOWNLINK_RRC: {
        handleDownlinkRrc(dynamic_cast<NwUeDownlinkRrc *>(msg));
        break;
    }
    case NtsMessageType::UE_UPLINK_NAS_DELIVERY: {
        deliverUplinkNas(std::move(dynamic_cast<NwUplinkNasDelivery *>(msg)->nasPdu));
        delete msg;
        break;
    }
    case NtsMessageType::UE_INITIAL_NAS_DELIVERY: {
        deliverInitialNas(*dynamic_cast<NwInitialNasDelivery *>(msg));
        delete msg;
        break;
    }
    case NtsMessageType::UE_MR_PLMN_SEARCH_REQUEST: {
        m_base->mrTask->push(msg);
        break;
    }
    case NtsMessageType::UE_MR_PLMN_SEARCH_RESPONSE: {
        m_base->nasTask->push(msg);
        break;
    }
    case NtsMessageType::UE_MR_PLMN_SEARCH_FAILURE: {
        m_base->nasTask->push(msg);
        break;
    }
    default:
        m_logger->err("Unhandled NTS message received with type %d", (int)msg->msgType);
        delete msg;
        break;
    }
}

} // namespace nr::ue