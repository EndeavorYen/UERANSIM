/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#ifndef	_ASN_RRC_Q_OffsetRange_H_
#define	_ASN_RRC_Q_OffsetRange_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ASN_RRC_Q_OffsetRange {
	ASN_RRC_Q_OffsetRange_dB_24	= 0,
	ASN_RRC_Q_OffsetRange_dB_22	= 1,
	ASN_RRC_Q_OffsetRange_dB_20	= 2,
	ASN_RRC_Q_OffsetRange_dB_18	= 3,
	ASN_RRC_Q_OffsetRange_dB_16	= 4,
	ASN_RRC_Q_OffsetRange_dB_14	= 5,
	ASN_RRC_Q_OffsetRange_dB_12	= 6,
	ASN_RRC_Q_OffsetRange_dB_10	= 7,
	ASN_RRC_Q_OffsetRange_dB_8	= 8,
	ASN_RRC_Q_OffsetRange_dB_6	= 9,
	ASN_RRC_Q_OffsetRange_dB_5	= 10,
	ASN_RRC_Q_OffsetRange_dB_4	= 11,
	ASN_RRC_Q_OffsetRange_dB_3	= 12,
	ASN_RRC_Q_OffsetRange_dB_2	= 13,
	ASN_RRC_Q_OffsetRange_dB_1	= 14,
	ASN_RRC_Q_OffsetRange_dB0	= 15,
	ASN_RRC_Q_OffsetRange_dB1	= 16,
	ASN_RRC_Q_OffsetRange_dB2	= 17,
	ASN_RRC_Q_OffsetRange_dB3	= 18,
	ASN_RRC_Q_OffsetRange_dB4	= 19,
	ASN_RRC_Q_OffsetRange_dB5	= 20,
	ASN_RRC_Q_OffsetRange_dB6	= 21,
	ASN_RRC_Q_OffsetRange_dB8	= 22,
	ASN_RRC_Q_OffsetRange_dB10	= 23,
	ASN_RRC_Q_OffsetRange_dB12	= 24,
	ASN_RRC_Q_OffsetRange_dB14	= 25,
	ASN_RRC_Q_OffsetRange_dB16	= 26,
	ASN_RRC_Q_OffsetRange_dB18	= 27,
	ASN_RRC_Q_OffsetRange_dB20	= 28,
	ASN_RRC_Q_OffsetRange_dB22	= 29,
	ASN_RRC_Q_OffsetRange_dB24	= 30
} e_ASN_RRC_Q_OffsetRange;

/* ASN_RRC_Q-OffsetRange */
typedef long	 ASN_RRC_Q_OffsetRange_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_ASN_RRC_Q_OffsetRange_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_ASN_RRC_Q_OffsetRange;
extern const asn_INTEGER_specifics_t asn_SPC_ASN_RRC_Q_OffsetRange_specs_1;
asn_struct_free_f ASN_RRC_Q_OffsetRange_free;
asn_struct_print_f ASN_RRC_Q_OffsetRange_print;
asn_constr_check_f ASN_RRC_Q_OffsetRange_constraint;
ber_type_decoder_f ASN_RRC_Q_OffsetRange_decode_ber;
der_type_encoder_f ASN_RRC_Q_OffsetRange_encode_der;
xer_type_decoder_f ASN_RRC_Q_OffsetRange_decode_xer;
xer_type_encoder_f ASN_RRC_Q_OffsetRange_encode_xer;
per_type_decoder_f ASN_RRC_Q_OffsetRange_decode_uper;
per_type_encoder_f ASN_RRC_Q_OffsetRange_encode_uper;
per_type_decoder_f ASN_RRC_Q_OffsetRange_decode_aper;
per_type_encoder_f ASN_RRC_Q_OffsetRange_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _ASN_RRC_Q_OffsetRange_H_ */
#include <asn_internal.h>
