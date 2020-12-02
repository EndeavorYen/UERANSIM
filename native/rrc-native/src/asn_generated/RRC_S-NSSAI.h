/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#ifndef	_RRC_S_NSSAI_H_
#define	_RRC_S_NSSAI_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRC_S_NSSAI_PR {
	RRC_S_NSSAI_PR_NOTHING,	/* No components present */
	RRC_S_NSSAI_PR_sst,
	RRC_S_NSSAI_PR_sst_SD
} RRC_S_NSSAI_PR;

/* RRC_S-NSSAI */
typedef struct RRC_S_NSSAI {
	RRC_S_NSSAI_PR present;
	union RRC_S_NSSAI_u {
		BIT_STRING_t	 sst;
		BIT_STRING_t	 sst_SD;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRC_S_NSSAI_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRC_S_NSSAI;
extern asn_CHOICE_specifics_t asn_SPC_RRC_S_NSSAI_specs_1;
extern asn_TYPE_member_t asn_MBR_RRC_S_NSSAI_1[2];
extern asn_per_constraints_t asn_PER_type_RRC_S_NSSAI_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _RRC_S_NSSAI_H_ */
#include <asn_internal.h>