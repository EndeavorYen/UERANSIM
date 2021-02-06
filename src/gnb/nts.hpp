//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include <rrc/rrc.hpp>
#include <sctp/sctp.hpp>
#include <urs/rls/rls.hpp>
#include <utility>
#include <utils/network.hpp>
#include <utils/nts.hpp>
#include <utils/octet_string.hpp>

#include "types.hpp"

namespace nr::gnb
{

struct NwGnbMrToRrc : NtsMessage
{
    enum PR
    {
        RRC_PDU_DELIVERY
    } present;

    // RRC_PDU_DELIVERY
    int ueId{};
    rrc::RrcChannel channel{};
    OctetString pdu{};

    explicit NwGnbMrToRrc(PR present) : NtsMessage(NtsMessageType::GNB_MR_TO_RRC), present(present)
    {
    }
};

struct NwGnbNgapToRrc : NtsMessage
{
    enum PR
    {
        NAS_DELIVERY
    } present;

    // NAS_DELIVERY
    int ueId{};
    OctetString pdu{};

    explicit NwGnbNgapToRrc(PR present) : NtsMessage(NtsMessageType::GNB_NGAP_TO_RRC), present(present)
    {
    }
};

struct NwGnbRrcToNgap : NtsMessage
{
    enum PR
    {
        INITIAL_NAS_DELIVERY,
        UPLINK_NAS_DELIVERY
    } present;

    // INITIAL_NAS_DELIVERY
    // UPLINK_NAS_DELIVERY
    int ueId{};
    OctetString pdu{};

    // INITIAL_NAS_DELIVERY
    long rrcEstablishmentCause{};

    explicit NwGnbRrcToNgap(PR present) : NtsMessage(NtsMessageType::GNB_RRC_TO_NGAP), present(present)
    {
    }
};

struct NwGnbSctp : NtsMessage
{
    enum PR
    {
        CONNECTION_REQUEST,
        CONNECTION_CLOSE,
        ASSOCIATION_SETUP,
        ASSOCIATION_SHUTDOWN,
        RECEIVE_MESSAGE,
        SEND_MESSAGE,
        UNHANDLED_NOTIFICATION,
    } present;

    // CONNECTION_REQUEST
    // CONNECTION_CLOSE
    // ASSOCIATION_SETUP
    // ASSOCIATION_SHUTDOWN
    // RECEIVE_MESSAGE
    // SEND_MESSAGE
    // UNHANDLED_NOTIFICATION
    int clientId{};

    // CONNECTION_REQUEST
    std::string localAddress{};
    uint16_t localPort{};
    std::string remoteAddress{};
    uint16_t remotePort{};
    sctp::PayloadProtocolId ppid{};
    NtsTask *associatedTask{};

    // ASSOCIATION_SETUP
    int associationId{};
    int inStreams{};
    int outStreams{};

    // RECEIVE_MESSAGE
    // SEND_MESSAGE
    const uint8_t *buffer{};
    size_t length{};
    uint16_t stream{};

    explicit NwGnbSctp(PR present) : NtsMessage(NtsMessageType::GNB_SCTP), present(present)
    {
    }

    ~NwGnbSctp() override
    {
        if (present == RECEIVE_MESSAGE)
            delete[] buffer; // This buffer was allocated using new()
        else if (present == SEND_MESSAGE)
            free((void *)buffer); // This buffer was allocated by asn1c library using malloc/calloc
    }
};

struct NwPduSessionResourceCreate : NtsMessage
{
    PduSessionResource *resource;

    explicit NwPduSessionResourceCreate(PduSessionResource *resource)
        : NtsMessage(NtsMessageType::NGAP_PDU_SESSION_RESOURCE_CREATE), resource(resource)
    {
    }
};

struct NwGnbStatusUpdate : NtsMessage
{
    static constexpr const int INITIAL_SCTP_ESTABLISHED = 1;

    const int what;

    // INITIAL_SCTP_ESTABLISHED
    bool isInitialSctpEstablished{};

    explicit NwGnbStatusUpdate(const int what) : NtsMessage(NtsMessageType::GNB_STATUS_UPDATE), what(what)
    {
    }
};

struct NwGnbN1Ready : NtsMessage
{
    NwGnbN1Ready() : NtsMessage(NtsMessageType::GNB_MR_N1_IS_READY)
    {
    }
};

struct NwUeContextUpdate : NtsMessage
{
    int ueId;
    bool isCreate;
    AggregateMaximumBitRate ueAmbr;

    NwUeContextUpdate(int ueId, bool isCreate, const AggregateMaximumBitRate &ueAmbr)
        : NtsMessage(NtsMessageType::GTP_UE_CONTEXT_UPDATE), ueId(ueId), isCreate(isCreate), ueAmbr(ueAmbr)
    {
    }
};

struct NwGnbDownlinkRrc : NtsMessage
{
    int ueId;
    rrc::RrcChannel channel;
    OctetString rrcPdu;

    NwGnbDownlinkRrc(int ueId, rrc::RrcChannel channel, OctetString &&rrcPdu)
        : NtsMessage(NtsMessageType::GNB_MR_DOWNLINK_RRC), ueId(ueId), channel(channel), rrcPdu(std::move(rrcPdu))
    {
    }
};

struct NwUplinkData : NtsMessage
{
    int ueId;
    int pduSessionId;
    OctetString data;

    NwUplinkData(int ueId, int pduSessionId, OctetString &&data)
        : NtsMessage(NtsMessageType::GNB_MR_UPLINK_DATA), ueId(ueId), pduSessionId(pduSessionId), data(std::move(data))
    {
    }
};

struct NwDownlinkData : NtsMessage
{
    int ueId;
    int pduSessionId;
    OctetString data;

    NwDownlinkData(int ueId, int pduSessionId, OctetString &&data)
        : NtsMessage(NtsMessageType::GNB_MR_DOWNLINK_DATA), ueId(ueId), pduSessionId(pduSessionId),
          data(std::move(data))
    {
    }
};

struct NwUeConnected : NtsMessage
{
    int ue;
    std::string name;

    NwUeConnected(int ue, std::string name)
        : NtsMessage(NtsMessageType::GNB_RLS_UE_CONNECTED), ue(ue), name(std::move(name))
    {
    }
};

struct NwUeReleased : NtsMessage
{
    int ue;
    rls::ECause cause;

    NwUeReleased(int ue, rls::ECause cause) : NtsMessage(NtsMessageType::GNB_RLS_UE_RELEASED), ue(ue), cause(cause)
    {
    }
};

struct NwUplinkPayload : NtsMessage
{
    int ue;
    rls::EPayloadType type;
    OctetString payload;

    NwUplinkPayload(int ue, rls::EPayloadType type, OctetString &&payload)
        : NtsMessage(NtsMessageType::GNB_RLS_UPLINK_PAYLOAD), ue(ue), type(type), payload(std::move(payload))
    {
    }
};

struct NwRlsSendPdu : NtsMessage
{
    InetAddress address;
    OctetString pdu;

    NwRlsSendPdu(const InetAddress &address, OctetString &&pdu)
        : NtsMessage(NtsMessageType::GNB_RLS_SEND_PDU), address(address), pdu(std::move(pdu))
    {
    }
};

} // namespace nr::gnb
