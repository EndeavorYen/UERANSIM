//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include <logger.hpp>
#include <nts.hpp>
#include <optional>
#include <unordered_map>

#include "gnb_app_task.hpp"
#include "gnb_config.hpp"
#include "gnb_gtp_task.hpp"
#include "gnb_rrc_task.hpp"
#include "gnb_sctp_task.hpp"
#include "gnb_types.hpp"

struct ASN_NGAP_NGAP_PDU;
struct ASN_NGAP_NGSetupResponse;
struct ASN_NGAP_NGSetupFailure;
struct ASN_NGAP_ErrorIndication;
struct ASN_NGAP_DownlinkNASTransport;
struct ASN_NGAP_RerouteNASRequest;
struct ASN_NGAP_PDUSessionResourceSetupRequest;
struct ASN_NGAP_InitialContextSetupRequest;
struct ASN_NGAP_UEContextReleaseCommand;
struct ASN_NGAP_UEContextModificationRequest;

namespace nr::gnb
{

class NgapTask : public NtsTask
{
  private:
    GnbConfig *config;
    std::unique_ptr<logger::Logger> logger;

    std::unordered_map<int, NgapAmfContext *> amfContexts;
    std::unordered_map<int, NgapUeContext *> ueContexts;
    long ueNgapIdCounter;

    int waitingSctpClients;
    uint32_t downlinkTeidCounter;

    SctpTask *sctpTask;
    GnbRrcTask *rrcTask;
    GtpTask *gtpTask;
    GnbAppTask *appTask;

  public:
    explicit NgapTask(GnbConfig *config, logger::LogBase &loggerBase);
    ~NgapTask() override = default;
    void setExternalTasks(SctpTask *sctpTask, GnbRrcTask *rrcTask, GtpTask *gtpTask, GnbAppTask *appTask);

  protected:
    void onStart() override;
    void onLoop() override;
    void onQuit() override;

  private:
    /* Utility functions */
    void createAmfContext(const GnbAmfConfig &config);
    NgapAmfContext *findAmfContext(int ctxId);
    void createUeContext(int ueId);
    NgapUeContext *findUeContext(int ctxId);
    NgapUeContext *findUeByRanId(long ranUeNgapId);
    NgapUeContext *findUeByAmfId(long amfUeNgapId);
    NgapUeContext *findUeByNgapIdPair(int amfCtxId, const NgapIdPair &idPair);
    NgapAmfContext *selectNewAmfForReAllocation(int initiatedAmfId, int amfSetId);
    void deleteUeContext(int ueId);

    /* Interface management */
    void sendNgSetupRequest(int amfId);
    void sendErrorIndication(int amfId, NgapCause cause = NgapCause::Protocol_unspecified, int ueId = 0);
    void receiveNgSetupResponse(int amfId, ASN_NGAP_NGSetupResponse *msg);
    void receiveNgSetupFailure(int amfId, ASN_NGAP_NGSetupFailure *msg);
    void receiveErrorIndication(int amfId, ASN_NGAP_ErrorIndication *msg);
    void handleAssociationSetup(NwSctpAssociationSetup *msg);

    /* Message transport */
    void sendNgapNonUe(int amfId, ASN_NGAP_NGAP_PDU *pdu);
    void sendNgapUeAssociated(int ueId, ASN_NGAP_NGAP_PDU *pdu);
    void handleSctpMessage(NwSctpClientReceive *msg);
    bool handleSctpStreamId(int amfId, int stream, const ASN_NGAP_NGAP_PDU &pdu);

    /* NAS transport */
    void handleInitialNasTransport(int ueId, const OctetString &nasPdu);
    void handleUplinkNasTransport(int ueId, const OctetString &nasPdu);
    void receiveDownlinkNasTransport(int amfId, ASN_NGAP_DownlinkNASTransport *msg);
    void deliverDownlinkNas(int ueId, OctetString &&nasPdu);
    void deliverUplinkNas(NwUplinkNasDelivery *msg);
    void sendNasNonDeliveryIndication(int ueId, const OctetString &nasPdu, NgapCause cause);
    void receiveRerouteNasRequest(int amfId, ASN_NGAP_RerouteNASRequest *msg);

    /* PDU session management */
    void receiveSessionResourceSetupRequest(int amfId, ASN_NGAP_PDUSessionResourceSetupRequest *msg);
    std::optional<NgapCause> setupPduSessionResource(PduSessionResource *resource);

    /* UE context management */
    void receiveInitialContextSetup(int amfId, ASN_NGAP_InitialContextSetupRequest *msg);
    void receiveContextRelease(int amfId, ASN_NGAP_UEContextReleaseCommand *msg);
    void receiveContextModification(int amfId, ASN_NGAP_UEContextModificationRequest *msg);
};

} // namespace nr::gnb