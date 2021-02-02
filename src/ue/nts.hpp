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

struct NwUeMrToMr : NtsMessage
{
    enum PR
    {
        RLS_CONNECTED,
        RLS_RELEASED,
        RLS_SEARCH_FAILURE,
        RLS_START_WAITING_TIMER,
        RLS_SEND_OVER_UDP,
        RLS_RECEIVE_OVER_UDP
    } present;

    // RLS_CONNECTED
    std::string gnbName{};

    // RLS_RELEASED
    // RLS_SEARCH_FAILURE
    rls::ECause cause{};

    // RLS_START_WAITING_TIMER
    int period{};

    // RLS_SEND_OVER_UDP
    InetAddress address{};

    // RLS_RECEIVE_OVER_UDP
    rls::EPayloadType type{};

    // RLS_SEND_OVER_UDP
    // RLS_RECEIVE_OVER_UDP
    OctetString pdu{};

    explicit NwUeMrToMr(PR present) : NtsMessage(NtsMessageType::UE_MR_TO_MR), present(present)
    {
    }
};

struct NwUeMrToRrc : NtsMessage
{
    enum PR
    {
        PLMN_SEARCH_RESPONSE,
        PLMN_SEARCH_FAILURE,
    } present;

    // PLMN_SEARCH_RESPONSE
    std::string gnbName{};

    explicit NwUeMrToRrc(PR present) : NtsMessage(NtsMessageType::UE_MR_TO_RRC), present(present)
    {
    }
};

struct NwUeRrcToNas : NtsMessage
{
    enum PR
    {
        NAS_DELIVERY,
        PLMN_SEARCH_RESPONSE,
        PLMN_SEARCH_FAILURE,
        RRC_CONNECTION_SETUP,
    } present;

    // NAS_DELIVERY
    OctetString nasPdu{};

    // PLMN_SEARCH_RESPONSE
    std::string gnbName{};

    explicit NwUeRrcToNas(PR present) : NtsMessage(NtsMessageType::UE_RRC_TO_NAS), present(present)
    {
    }
};

struct NwUeNasToRrc : NtsMessage
{
    enum PR
    {
        PLMN_SEARCH_REQUEST,
        INITIAL_NAS_DELIVERY,
        UPLINK_NAS_DELIVERY
    } present;

    // INITIAL_NAS_DELIVERY
    // UPLINK_NAS_DELIVERY
    OctetString nasPdu{};

    // INITIAL_NAS_DELIVERY
    long rrcEstablishmentCause{};

    explicit NwUeNasToRrc(PR present) : NtsMessage(NtsMessageType::UE_NAS_TO_RRC), present(present)
    {
    }
};

struct NwUeRrcToMr : NtsMessage
{
    enum PR
    {
        PLMN_SEARCH_REQUEST,
    } present;

    explicit NwUeRrcToMr(PR present) : NtsMessage(NtsMessageType::UE_RRC_TO_MR), present(present)
    {
    }
};

struct NwUeNasToNas : NtsMessage
{
    enum PR
    {
        PERFORM_MM_CYCLE,
        NAS_TIMER_EXPIRE,
        ESTABLISH_INITIAL_SESSIONS
    } present;

    // NAS_TIMER_EXPIRE
    nas::NasTimer *timer{};

    explicit NwUeNasToNas(PR present) : NtsMessage(NtsMessageType::UE_NAS_TO_NAS), present(present)
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

} // namespace nr::ue