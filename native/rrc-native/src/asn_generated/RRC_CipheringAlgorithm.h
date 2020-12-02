/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#ifndef	_RRC_CipheringAlgorithm_H_
#define	_RRC_CipheringAlgorithm_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRC_CipheringAlgorithm {
	RRC_CipheringAlgorithm_nea0	= 0,
	RRC_CipheringAlgorithm_nea1	= 1,
	RRC_CipheringAlgorithm_nea2	= 2,
	RRC_CipheringAlgorithm_nea3	= 3,
	RRC_CipheringAlgorithm_spare4	= 4,
	RRC_CipheringAlgorithm_spare3	= 5,
	RRC_CipheringAlgorithm_spare2	= 6,
	RRC_CipheringAlgorithm_spare1	= 7
	/*
	 * Enumeration is extensible
	 */
} e_RRC_CipheringAlgorithm;

/* RRC_CipheringAlgorithm */
typedef long	 RRC_CipheringAlgorithm_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_RRC_CipheringAlgorithm_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_RRC_CipheringAlgorithm;
extern const asn_INTEGER_specifics_t asn_SPC_RRC_CipheringAlgorithm_specs_1;
asn_struct_free_f RRC_CipheringAlgorithm_free;
asn_struct_print_f RRC_CipheringAlgorithm_print;
asn_constr_check_f RRC_CipheringAlgorithm_constraint;
ber_type_decoder_f RRC_CipheringAlgorithm_decode_ber;
der_type_encoder_f RRC_CipheringAlgorithm_encode_der;
xer_type_decoder_f RRC_CipheringAlgorithm_decode_xer;
xer_type_encoder_f RRC_CipheringAlgorithm_encode_xer;
per_type_decoder_f RRC_CipheringAlgorithm_decode_uper;
per_type_encoder_f RRC_CipheringAlgorithm_encode_uper;
per_type_decoder_f RRC_CipheringAlgorithm_decode_aper;
per_type_encoder_f RRC_CipheringAlgorithm_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _RRC_CipheringAlgorithm_H_ */
#include <asn_internal.h>