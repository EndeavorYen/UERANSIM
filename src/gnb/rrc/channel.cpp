//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "task.hpp"
#include <asn/rrc/ASN_RRC_UL-CCCH-Message.h>
#include <asn/rrc/ASN_RRC_UL-DCCH-Message.h>
#include <rrc/encode.hpp>

namespace nr::gnb
{

void GnbRrcTask::handleUplinkRrc(int ueId, rrc::RrcChannel channel, const OctetString &rrcPdu)
{
    switch (channel)
    {
    case rrc::RrcChannel::BCCH_BCH: {
        auto *pdu = rrc::encode::Decode<ASN_RRC_BCCH_BCH_Message>(asn_DEF_ASN_RRC_BCCH_BCH_Message, rrcPdu);
        if (pdu == nullptr)
            m_logger->err("RRC BCCH-BCH PDU decoding failed.");
        else
            receiveRrcMessage(ueId, pdu);
        asn::Free(asn_DEF_ASN_RRC_BCCH_BCH_Message, pdu);
        break;
    }
    case rrc::RrcChannel::BCCH_DL_SCH: {
        auto *pdu = rrc::encode::Decode<ASN_RRC_BCCH_DL_SCH_Message>(asn_DEF_ASN_RRC_BCCH_DL_SCH_Message, rrcPdu);
        if (pdu == nullptr)
            m_logger->err("RRC BCCH-DL-SCH PDU decoding failed.");
        else
            receiveRrcMessage(ueId, pdu);
        asn::Free(asn_DEF_ASN_RRC_BCCH_DL_SCH_Message, pdu);
        break;
    }
    case rrc::RrcChannel::DL_CCCH: {
        auto *pdu = rrc::encode::Decode<ASN_RRC_DL_CCCH_Message>(asn_DEF_ASN_RRC_DL_CCCH_Message, rrcPdu);
        if (pdu == nullptr)
            m_logger->err("RRC DL-CCCH PDU decoding failed.");
        else
            receiveRrcMessage(ueId, pdu);
        asn::Free(asn_DEF_ASN_RRC_DL_CCCH_Message, pdu);
        break;
    }
    case rrc::RrcChannel::DL_DCCH: {
        auto *pdu = rrc::encode::Decode<ASN_RRC_DL_DCCH_Message>(asn_DEF_ASN_RRC_DL_DCCH_Message, rrcPdu);
        if (pdu == nullptr)
            m_logger->err("RRC DL-DCCH PDU decoding failed.");
        else
            receiveRrcMessage(ueId, pdu);
        asn::Free(asn_DEF_ASN_RRC_DL_DCCH_Message, pdu);
        break;
    }
    case rrc::RrcChannel::PCCH: {
        auto *pdu = rrc::encode::Decode<ASN_RRC_PCCH_Message>(asn_DEF_ASN_RRC_PCCH_Message, rrcPdu);
        if (pdu == nullptr)
            m_logger->err("RRC PCCH PDU decoding failed.");
        else
            receiveRrcMessage(ueId, pdu);
        asn::Free(asn_DEF_ASN_RRC_PCCH_Message, pdu);
        break;
    }
    case rrc::RrcChannel::UL_CCCH: {
        auto *pdu = rrc::encode::Decode<ASN_RRC_UL_CCCH_Message>(asn_DEF_ASN_RRC_UL_CCCH_Message, rrcPdu);
        if (pdu == nullptr)
            m_logger->err("RRC UL-CCCH PDU decoding failed.");
        else
            receiveRrcMessage(ueId, pdu);
        asn::Free(asn_DEF_ASN_RRC_UL_CCCH_Message, pdu);
        break;
    }
    case rrc::RrcChannel::UL_CCCH1: {
        auto *pdu = rrc::encode::Decode<ASN_RRC_UL_CCCH1_Message>(asn_DEF_ASN_RRC_UL_CCCH1_Message, rrcPdu);
        if (pdu == nullptr)
            m_logger->err("RRC UL-CCCH1 PDU decoding failed.");
        else
            receiveRrcMessage(ueId, pdu);
        asn::Free(asn_DEF_ASN_RRC_UL_CCCH1_Message, pdu);
        break;
    }
    case rrc::RrcChannel::UL_DCCH: {
        auto *pdu = rrc::encode::Decode<ASN_RRC_UL_DCCH_Message>(asn_DEF_ASN_RRC_UL_DCCH_Message, rrcPdu);
        if (pdu == nullptr)
            m_logger->err("RRC UL-DCCH PDU decoding failed.");
        else
            receiveRrcMessage(ueId, pdu);
        asn::Free(asn_DEF_ASN_RRC_UL_DCCH_Message, pdu);
        break;
    }
    }
}

void GnbRrcTask::sendRrcMessage(int ueId, ASN_RRC_BCCH_BCH_Message *msg)
{
    OctetString pdu = rrc::encode::EncodeS(asn_DEF_ASN_RRC_BCCH_BCH_Message, msg);
    if (pdu.length() == 0)
    {
        m_logger->err("RRC BCCH-BCH encoding failed.");
        return;
    }
    m_base->mrTask->push(new NwGnbDownlinkRrc(ueId, rrc::RrcChannel::BCCH_BCH, std::move(pdu)));
}

void GnbRrcTask::sendRrcMessage(int ueId, ASN_RRC_BCCH_DL_SCH_Message *msg)
{
    OctetString pdu = rrc::encode::EncodeS(asn_DEF_ASN_RRC_BCCH_DL_SCH_Message, msg);
    if (pdu.length() == 0)
    {
        m_logger->err("RRC BCCH-DL-SCH encoding failed.");
        return;
    }
    m_base->mrTask->push(new NwGnbDownlinkRrc(ueId, rrc::RrcChannel::BCCH_DL_SCH, std::move(pdu)));
}

void GnbRrcTask::sendRrcMessage(int ueId, ASN_RRC_DL_CCCH_Message *msg)
{
    OctetString pdu = rrc::encode::EncodeS(asn_DEF_ASN_RRC_DL_CCCH_Message, msg);
    if (pdu.length() == 0)
    {
        m_logger->err("RRC DL-CCCH encoding failed.");
        return;
    }
    m_base->mrTask->push(new NwGnbDownlinkRrc(ueId, rrc::RrcChannel::DL_CCCH, std::move(pdu)));
}

void GnbRrcTask::sendRrcMessage(int ueId, ASN_RRC_DL_DCCH_Message *msg)
{
    OctetString pdu = rrc::encode::EncodeS(asn_DEF_ASN_RRC_DL_DCCH_Message, msg);
    if (pdu.length() == 0)
    {
        m_logger->err("RRC DL-DCCH encoding failed.");
        return;
    }
    m_base->mrTask->push(new NwGnbDownlinkRrc(ueId, rrc::RrcChannel::DL_DCCH, std::move(pdu)));
}

void GnbRrcTask::sendRrcMessage(int ueId, ASN_RRC_PCCH_Message *msg)
{
    OctetString pdu = rrc::encode::EncodeS(asn_DEF_ASN_RRC_PCCH_Message, msg);
    if (pdu.length() == 0)
    {
        m_logger->err("RRC PCCH encoding failed.");
        return;
    }
    m_base->mrTask->push(new NwGnbDownlinkRrc(ueId, rrc::RrcChannel::PCCH, std::move(pdu)));
}

void GnbRrcTask::sendRrcMessage(int ueId, ASN_RRC_UL_CCCH_Message *msg)
{
    OctetString pdu = rrc::encode::EncodeS(asn_DEF_ASN_RRC_UL_CCCH_Message, msg);
    if (pdu.length() == 0)
    {
        m_logger->err("RRC UL-CCCH encoding failed.");
        return;
    }
    m_base->mrTask->push(new NwGnbDownlinkRrc(ueId, rrc::RrcChannel::UL_CCCH, std::move(pdu)));
}

void GnbRrcTask::sendRrcMessage(int ueId, ASN_RRC_UL_CCCH1_Message *msg)
{
    OctetString pdu = rrc::encode::EncodeS(asn_DEF_ASN_RRC_UL_CCCH1_Message, msg);
    if (pdu.length() == 0)
    {
        m_logger->err("RRC UL-CCCH1 encoding failed.");
        return;
    }
    m_base->mrTask->push(new NwGnbDownlinkRrc(ueId, rrc::RrcChannel::UL_CCCH1, std::move(pdu)));
}

void GnbRrcTask::sendRrcMessage(int ueId, ASN_RRC_UL_DCCH_Message *msg)
{
    OctetString pdu = rrc::encode::EncodeS(asn_DEF_ASN_RRC_UL_DCCH_Message, msg);
    if (pdu.length() == 0)
    {
        m_logger->err("RRC UL-DCCH encoding failed.");
        return;
    }
    m_base->mrTask->push(new NwGnbDownlinkRrc(ueId, rrc::RrcChannel::UL_DCCH, std::move(pdu)));
}

void GnbRrcTask::receiveRrcMessage(int ueId, ASN_RRC_BCCH_BCH_Message *msg)
{
    // TODO
}

void GnbRrcTask::receiveRrcMessage(int ueId, ASN_RRC_BCCH_DL_SCH_Message *msg)
{
    // TODO
}

void GnbRrcTask::receiveRrcMessage(int ueId, ASN_RRC_DL_CCCH_Message *msg)
{
    // TODO
}

void GnbRrcTask::receiveRrcMessage(int ueId, ASN_RRC_DL_DCCH_Message *msg)
{
    // TODO
}

void GnbRrcTask::receiveRrcMessage(int ueId, ASN_RRC_PCCH_Message *msg)
{
    // TODO
}

void GnbRrcTask::receiveRrcMessage(int ueId, ASN_RRC_UL_CCCH_Message *msg)
{
    if (msg->message.present != ASN_RRC_UL_CCCH_MessageType_PR_c1)
        return;

    auto &c1 = msg->message.choice.c1;
    switch (c1->present)
    {
    case ASN_RRC_UL_CCCH_MessageType__c1_PR_NOTHING:
        return;
    case ASN_RRC_UL_CCCH_MessageType__c1_PR_rrcSetupRequest:
        receiveRrcSetupRequest(ueId, *c1->choice.rrcSetupRequest);
        break;
    case ASN_RRC_UL_CCCH_MessageType__c1_PR_rrcResumeRequest:
        break; // todo
    case ASN_RRC_UL_CCCH_MessageType__c1_PR_rrcReestablishmentRequest:
        break; // todo
    case ASN_RRC_UL_CCCH_MessageType__c1_PR_rrcSystemInfoRequest:
        break; // todo
    }
}

void GnbRrcTask::receiveRrcMessage(int ueId, ASN_RRC_UL_CCCH1_Message *msg)
{
    // TODO
}

void GnbRrcTask::receiveRrcMessage(int ueId, ASN_RRC_UL_DCCH_Message *msg)
{
    if (msg->message.present != ASN_RRC_UL_DCCH_MessageType_PR_c1)
        return;

    auto &c1 = msg->message.choice.c1;
    switch (c1->present)
    {
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_NOTHING:
        return;
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_measurementReport:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_rrcReconfigurationComplete:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_rrcSetupComplete:
        receiveRrcSetupComplete(ueId, *c1->choice.rrcSetupComplete);
        break;
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_rrcReestablishmentComplete:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_rrcResumeComplete:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_securityModeComplete:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_securityModeFailure:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_ulInformationTransfer:
        receiveUplinkInformationTransfer(ueId, *c1->choice.ulInformationTransfer);
        break;
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_locationMeasurementIndication:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_ueCapabilityInformation:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_counterCheckResponse:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_ueAssistanceInformation:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_failureInformation:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_ulInformationTransferMRDC:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_scgFailureInformation:
        break; // TODO
    case ASN_RRC_UL_DCCH_MessageType__c1_PR_scgFailureInformationEUTRA:
        break; // TODO
    }
}

} // namespace nr::gnb