//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include "types.hpp"
#include <nas/timer.hpp>
#include <rrc/rrc.hpp>
#include <urs/rls/rls.hpp>
#include <utility>
#include <utils/network.hpp>
#include <utils/nts.hpp>
#include <utils/octet_string.hpp>

namespace nr::ue
{

struct NwDownlinkNasDelivery : NtsMessage
{
    OctetString nasPdu;

    explicit NwDownlinkNasDelivery(OctetString &&nasPdu)
        : NtsMessage(NtsMessageType::UE_DOWNLINK_NAS_DELIVERY), nasPdu(std::move(nasPdu))
    {
    }
};

struct NwUplinkNasDelivery : NtsMessage
{
    OctetString nasPdu;

    explicit NwUplinkNasDelivery(OctetString &&nasPdu)
        : NtsMessage(NtsMessageType::UE_UPLINK_NAS_DELIVERY), nasPdu(std::move(nasPdu))
    {
    }
};

struct NwInitialNasDelivery : NtsMessage
{
    OctetString nasPdu;
    long rrcEstablishmentCause;

    NwInitialNasDelivery(OctetString &&nasPdu, long rrcEstablishmentCause)
        : NtsMessage(NtsMessageType::UE_INITIAL_NAS_DELIVERY), nasPdu(std::move(nasPdu)),
          rrcEstablishmentCause(rrcEstablishmentCause)
    {
    }
};

struct NwNasTimerExpire : NtsMessage
{
    nas::NasTimer *timer;

    explicit NwNasTimerExpire(nas::NasTimer *timer) : NtsMessage(NtsMessageType::NAS_TIMER_EXPIRE), timer(timer)
    {
    }
};

struct NwPlmnSearchRequest : NtsMessage
{
    NwPlmnSearchRequest() : NtsMessage(NtsMessageType::UE_MR_PLMN_SEARCH_REQUEST)
    {
    }
};

struct NwPlmnSearchResponse : NtsMessage
{
    std::string gnbName;

    explicit NwPlmnSearchResponse(std::string gnbName)
        : NtsMessage(NtsMessageType::UE_MR_PLMN_SEARCH_RESPONSE), gnbName(std::move(gnbName))
    {
    }
};

struct NwPlmnSearchFailure : NtsMessage
{
    NwPlmnSearchFailure() : NtsMessage(NtsMessageType::UE_MR_PLMN_SEARCH_FAILURE)
    {
    }
};

struct NwPerformMmCycle : NtsMessage
{
    NwPerformMmCycle() : NtsMessage(NtsMessageType::NAS_PERFORM_MM_CYCLE)
    {
    }
};

struct NwUeUplinkRrc : NtsMessage
{
    rrc::RrcChannel channel;
    OctetString rrcPdu;

    NwUeUplinkRrc(rrc::RrcChannel channel, OctetString &&rrcPdu)
        : NtsMessage(NtsMessageType::UE_MR_UPLINK_RRC), channel(channel), rrcPdu(std::move(rrcPdu))
    {
    }
};

struct NwUeDownlinkRrc : NtsMessage
{
    rrc::RrcChannel channel;
    OctetString rrcPdu;

    NwUeDownlinkRrc(rrc::RrcChannel channel, OctetString &&rrcPdu)
        : NtsMessage(NtsMessageType::UE_MR_DOWNLINK_RRC), channel(channel), rrcPdu(std::move(rrcPdu))
    {
    }
};

struct NwRlsConnected : NtsMessage
{
    std::string gnbName;

    explicit NwRlsConnected(std::string gnbName)
        : NtsMessage(NtsMessageType::UE_RLS_CONNECTED), gnbName(std::move(gnbName))
    {
    }
};

struct NwRlsReleased : NtsMessage
{
    rls::ECause cause;

    explicit NwRlsReleased(rls::ECause cause) : NtsMessage(NtsMessageType::UE_RLS_RELEASED), cause(cause)
    {
    }
};

struct NwRlsSearchFailure : NtsMessage
{
    rls::ECause cause;

    explicit NwRlsSearchFailure(rls::ECause cause) : NtsMessage(NtsMessageType::UE_RLS_SEARCH_FAILURE), cause(cause)
    {
    }
};

struct NwRlsStartWaitingTimer : NtsMessage
{
    int period;

    explicit NwRlsStartWaitingTimer(int period) : NtsMessage(NtsMessageType::UE_RLS_START_WAITING_TIMER), period(period)
    {
    }
};

struct NwDownlinkPayload : NtsMessage
{
    rls::EPayloadType type;
    OctetString payload;

    NwDownlinkPayload(rls::EPayloadType type, OctetString &&payload)
        : NtsMessage(NtsMessageType::UE_RLS_DOWNLINK_PAYLOAD), type(type), payload(std::move(payload))
    {
    }
};

struct NwRlsSendPdu : NtsMessage
{
    InetAddress address;
    OctetString pdu;

    NwRlsSendPdu(const InetAddress &address, OctetString &&pdu)
        : NtsMessage(NtsMessageType::UE_RLS_SEND_PDU), address(address), pdu(std::move(pdu))
    {
    }
};

struct NwTriggerInitialSessionCreate : NtsMessage
{
    NwTriggerInitialSessionCreate() : NtsMessage(NtsMessageType::UE_TRIGGER_INITIAL_SESSION_CREATE)
    {
    }
};

struct NwUeStatusUpdate : NtsMessage
{
    static constexpr const int CONNECTED_GNB = 1;
    static constexpr const int MM_STATE = 2;
    static constexpr const int RM_STATE = 3;
    static constexpr const int CM_STATE = 4;
    static constexpr const int SESSION_ESTABLISHMENT = 5;

    const int what{};

    // CONNECTED_GNB
    std::string gnbName{};

    // MM_STATE
    std::string mmState{};
    std::string mmSubState{};

    // RM_STATE
    std::string rmState{};

    // CM_STATE
    std::string cmState{};

    // SESSION_ESTABLISHMENT
    PduSession *pduSession{};

    explicit NwUeStatusUpdate(const int what) : NtsMessage(NtsMessageType::UE_STATUS_UPDATE), what(what)
    {
    }
};

struct NwTunReceive : NtsMessage
{
    int psi;
    OctetString data;

    NwTunReceive(int psi, OctetString &&data)
        : NtsMessage(NtsMessageType::UE_TUN_RECEIVE), psi(psi), data(std::move(data))
    {
    }
};

struct NwTunError : NtsMessage
{
    std::string error;

    explicit NwTunError(std::string error) : NtsMessage(NtsMessageType::UE_TUN_ERROR), error(std::move(error))
    {
    }
};

struct NwUeUplinkData : NtsMessage
{
    int psi;
    OctetString data;

    explicit NwUeUplinkData(int psi, OctetString &&data)
        : NtsMessage(NtsMessageType::UE_MR_UPLINK_DATA), psi(psi), data(std::move(data))
    {
    }
};

struct NwUeDownlinkData : NtsMessage
{
    int psi;
    OctetString data;

    NwUeDownlinkData(int psi, OctetString &&data)
        : NtsMessage(NtsMessageType::UE_MR_DOWNLINK_DATA), psi(psi), data(std::move(data))
    {
    }
};

struct NwUeRrcConnectionSetup : NtsMessage
{
    NwUeRrcConnectionSetup() : NtsMessage(NtsMessageType::UE_RRC_CONNECTION_SETUP)
    {
    }
};

} // namespace nr::ue