//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "task.hpp"
#include <asn/rrc/ASN_RRC_DLInformationTransfer-IEs.h>
#include <asn/rrc/ASN_RRC_DLInformationTransfer.h>
#include <gnb/nts.hpp>
#include <rrc/encode.hpp>

namespace nr::gnb
{

GnbRrcTask::GnbRrcTask(TaskBase *base) : m_base{base}, m_ueCtx{}, m_tidCounter{}
{
    m_logger = base->logBase->makeUniqueLogger("rrc");
}

void GnbRrcTask::onStart()
{
}

void GnbRrcTask::onQuit()
{
    // todo
}

void GnbRrcTask::onLoop()
{
    NtsMessage *msg = take();
    if (!msg)
        return;

    switch (msg->msgType)
    {
    case NtsMessageType::NGAP_DOWNLINK_NAS_DELIVERY:
        handleDownlinkNasDelivery(dynamic_cast<NwDownlinkNasDelivery *>(msg));
        break;
    case NtsMessageType::GNB_MR_TO_RRC: {
        auto *w = dynamic_cast<NwGnbMrToRrc *>(msg);
        switch (w->present)
        {
        case NwGnbMrToRrc::RRC_PDU_DELIVERY: {
            handleUplinkRrc(w->ueId, w->channel, w->pdu);
            break;
        }
        }
        delete w;
        break;
    }
    default:
        m_logger->err("Unhandled NTS message received with type %d", (int)msg->msgType);
        delete msg;
        break;
    }
}

} // namespace nr::gnb
