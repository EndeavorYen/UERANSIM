/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#ifndef	_ASN_RRC_RadioLinkMonitoringRS_H_
#define	_ASN_RRC_RadioLinkMonitoringRS_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ASN_RRC_RadioLinkMonitoringRS-Id.h"
#include <NativeEnumerated.h>
#include "ASN_RRC_SSB-Index.h"
#include "ASN_RRC_NZP-CSI-RS-ResourceId.h"
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ASN_RRC_RadioLinkMonitoringRS__purpose {
	ASN_RRC_RadioLinkMonitoringRS__purpose_beamFailure	= 0,
	ASN_RRC_RadioLinkMonitoringRS__purpose_rlf	= 1,
	ASN_RRC_RadioLinkMonitoringRS__purpose_both	= 2
} e_ASN_RRC_RadioLinkMonitoringRS__purpose;
typedef enum ASN_RRC_RadioLinkMonitoringRS__detectionResource_PR {
	ASN_RRC_RadioLinkMonitoringRS__detectionResource_PR_NOTHING,	/* No components present */
	ASN_RRC_RadioLinkMonitoringRS__detectionResource_PR_ssb_Index,
	ASN_RRC_RadioLinkMonitoringRS__detectionResource_PR_csi_RS_Index
} ASN_RRC_RadioLinkMonitoringRS__detectionResource_PR;

/* ASN_RRC_RadioLinkMonitoringRS */
typedef struct ASN_RRC_RadioLinkMonitoringRS {
	ASN_RRC_RadioLinkMonitoringRS_Id_t	 radioLinkMonitoringRS_Id;
	long	 purpose;
	struct ASN_RRC_RadioLinkMonitoringRS__detectionResource {
		ASN_RRC_RadioLinkMonitoringRS__detectionResource_PR present;
		union ASN_RRC_RadioLinkMonitoringRS__ASN_RRC_detectionResource_u {
			ASN_RRC_SSB_Index_t	 ssb_Index;
			ASN_RRC_NZP_CSI_RS_ResourceId_t	 csi_RS_Index;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} detectionResource;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ASN_RRC_RadioLinkMonitoringRS_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_ASN_RRC_purpose_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_ASN_RRC_RadioLinkMonitoringRS;
extern asn_SEQUENCE_specifics_t asn_SPC_ASN_RRC_RadioLinkMonitoringRS_specs_1;
extern asn_TYPE_member_t asn_MBR_ASN_RRC_RadioLinkMonitoringRS_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _ASN_RRC_RadioLinkMonitoringRS_H_ */
#include <asn_internal.h>
