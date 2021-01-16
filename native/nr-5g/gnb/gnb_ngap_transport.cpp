//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "gnb_ngap_encode.hpp"
#include "gnb_ngap_task.hpp"
#include "gnb_ngap_utils.hpp"
#include "gnb_nts.hpp"

#include <asn_ngap.hpp>
#include <asn_utils.hpp>

#include <ASN_NGAP_AMF-UE-NGAP-ID.h>
#include <ASN_NGAP_InitiatingMessage.h>
#include <ASN_NGAP_NGAP-PDU.h>
#include <ASN_NGAP_ProtocolIE-Field.h>
#include <ASN_NGAP_RAN-UE-NGAP-ID.h>
#include <ASN_NGAP_SuccessfulOutcome.h>
#include <ASN_NGAP_UnsuccessfulOutcome.h>
#include <ASN_NGAP_UserLocationInformation.h>
#include <ASN_NGAP_UserLocationInformationNR.h>

namespace nr::gnb
{

void NgapTask::sendNgapNonUe(int associatedAmf, ASN_NGAP_NGAP_PDU *pdu)
{
    auto *amf = findAmfContext(associatedAmf);
    if (amf == nullptr)
    {
        asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
        return;
    }

    char errorBuffer[1024];
    size_t len;

    if (asn_check_constraints(&asn_DEF_ASN_NGAP_NGAP_PDU, pdu, errorBuffer, &len) != 0)
    {
        logger->err("NGAP PDU ASN constraint validation failed");
        asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
        return;
    }

    ssize_t encoded;
    uint8_t *buffer;
    if (!ngap_encode::Encode(asn_DEF_ASN_NGAP_NGAP_PDU, pdu, encoded, buffer))
        logger->err("NGAP APER encoding failed");
    else
    {
        auto *msg = new NwSctpSendMessage(amf->ctxId, 0, buffer, 0, static_cast<size_t>(encoded));
        sctpTask->push(msg);
        logger->debug("Non-UE-associated NGAP PDU with length %d is sent to SCTP layer", encoded);

        // todo: trigger OnSend
    }

    asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
}

void NgapTask::sendNgapUeAssociated(int ueId, ASN_NGAP_NGAP_PDU *pdu)
{
    /* Find UE and AMF contexts */

    auto *ue = findUeContext(ueId);
    if (ue == nullptr)
    {
        asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
        return;
    }

    auto *amf = findAmfContext(ue->associatedAmfId);
    if (amf == nullptr)
    {
        asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
        return;
    }

    /* Insert UE-related information elements */
    {
        if (ue->amfUeNgapId > 0)
        {
            asn::ngap::AddProtocolIeIfUsable(*pdu, asn_DEF_ASN_NGAP_AMF_UE_NGAP_ID,
                                             ASN_NGAP_ProtocolIE_ID_id_AMF_UE_NGAP_ID, ASN_NGAP_Criticality_reject,
                                             [ue](void *mem) {
                                                 auto &id = *reinterpret_cast<ASN_NGAP_AMF_UE_NGAP_ID_t *>(mem);
                                                 asn::SetSigned64(ue->amfUeNgapId, id);
                                             });
        }

        asn::ngap::AddProtocolIeIfUsable(
            *pdu, asn_DEF_ASN_NGAP_RAN_UE_NGAP_ID, ASN_NGAP_ProtocolIE_ID_id_RAN_UE_NGAP_ID,
            ASN_NGAP_Criticality_reject,
            [ue](void *mem) { *reinterpret_cast<ASN_NGAP_RAN_UE_NGAP_ID_t *>(mem) = ue->ranUeNgapId; });

        asn::ngap::AddProtocolIeIfUsable(
            *pdu, asn_DEF_ASN_NGAP_UserLocationInformation, ASN_NGAP_ProtocolIE_ID_id_UserLocationInformation,
            ASN_NGAP_Criticality_ignore, [this](void *mem) {
                auto *loc = reinterpret_cast<ASN_NGAP_UserLocationInformation *>(mem);
                loc->present = ASN_NGAP_UserLocationInformation_PR_userLocationInformationNR;

                auto &nr = loc->choice.userLocationInformationNR;

                ngap_utils::ToPlmnAsn_Ref(config->plmn, nr->nR_CGI.pLMNIdentity);
                asn::SetBitStringLong<36>(config->nci, nr->nR_CGI.nRCellIdentity);
                ngap_utils::ToPlmnAsn_Ref(config->plmn, nr->tAI.pLMNIdentity);
                asn::SetOctetString(nr->tAI.tAC, octet3{config->tac});
                asn::SetOctetString(*nr->timeStamp, octet4{utils::CurrentTimeStamp().seconds32()});
            });
    }

    /* Encode and send the PDU */

    char errorBuffer[1024];
    size_t len;

    if (asn_check_constraints(&asn_DEF_ASN_NGAP_NGAP_PDU, pdu, errorBuffer, &len) != 0)
    {
        logger->err("NGAP PDU ASN constraint validation failed");
        asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
        return;
    }

    ssize_t encoded;
    uint8_t *buffer;
    if (!ngap_encode::Encode(asn_DEF_ASN_NGAP_NGAP_PDU, pdu, encoded, buffer))
        logger->err("NGAP APER encoding failed");
    else
    {
        auto *msg = new NwSctpSendMessage(amf->ctxId, 0, buffer, 0, static_cast<size_t>(encoded));
        sctpTask->push(msg);
        logger->debug("UE-associated NGAP PDU with length %d is sent to SCTP layer", encoded);

        // todo: trigger OnSend
    }

    asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
}

void NgapTask::receiveSctpMessage(NwSctpClientReceive *msg)
{
    auto *amf = findAmfContext(msg->clientId);
    if (amf == nullptr)
    {
        delete msg;
        return;
    }

    auto *pdu = ngap_encode::Decode<ASN_NGAP_NGAP_PDU>(asn_DEF_ASN_NGAP_NGAP_PDU, msg->buffer, msg->length);
    if (pdu == nullptr)
    {
        logger->err("APER decoding failed for SCTP message");
        asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
        sendErrorIndication(msg->clientId, NgapCause::Protocol_transfer_syntax_error);
        delete msg;
        return;
    }

    if (pdu->present == ASN_NGAP_NGAP_PDU_PR_initiatingMessage)
    {
        auto value = pdu->choice.initiatingMessage->value;
        switch (value.present)
        {
        case ASN_NGAP_InitiatingMessage__value_PR_ErrorIndication:
            receiveErrorIndication(amf->ctxId, &value.choice.ErrorIndication);
            break;
        default:
            logger->err("Unhandled NGAP initiating-message received (%d)", value.present);
            break;
        }
    }
    else if (pdu->present == ASN_NGAP_NGAP_PDU_PR_successfulOutcome)
    {
        auto value = pdu->choice.successfulOutcome->value;
        switch (value.present)
        {
        case ASN_NGAP_SuccessfulOutcome__value_PR_NGSetupResponse:
            receiveNgSetupResponse(amf->ctxId, &value.choice.NGSetupResponse);
            break;
        default:
            logger->err("Unhandled NGAP successful-outcome received (%d)", value.present);
            break;
        }
    }
    else if (pdu->present == ASN_NGAP_NGAP_PDU_PR_unsuccessfulOutcome)
    {
        auto value = pdu->choice.unsuccessfulOutcome->value;
        switch (value.present)
        {
        case ASN_NGAP_UnsuccessfulOutcome__value_PR_NGSetupFailure:
            receiveNgSetupFailure(amf->ctxId, &value.choice.NGSetupFailure);
            break;
        default:
            logger->err("Unhandled NGAP unsuccessful-outcome received (%d)", value.present);
            break;
        }
    }
    else
    {
        logger->warn("Empty NGAP PDU ignored");
    }

    asn::Free(asn_DEF_ASN_NGAP_NGAP_PDU, pdu);
    delete msg;
}

} // namespace nr::gnb