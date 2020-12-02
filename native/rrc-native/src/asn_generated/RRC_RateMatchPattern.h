/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#ifndef	_RRC_RateMatchPattern_H_
#define	_RRC_RateMatchPattern_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RRC_RateMatchPatternId.h"
#include "RRC_SubcarrierSpacing.h"
#include <NativeEnumerated.h>
#include "RRC_ControlResourceSetId.h"
#include <BIT_STRING.h>
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRC_RateMatchPattern__patternType_PR {
	RRC_RateMatchPattern__patternType_PR_NOTHING,	/* No components present */
	RRC_RateMatchPattern__patternType_PR_bitmaps,
	RRC_RateMatchPattern__patternType_PR_controlResourceSet
} RRC_RateMatchPattern__patternType_PR;
typedef enum RRC_RateMatchPattern__patternType__bitmaps__symbolsInResourceBlock_PR {
	RRC_RateMatchPattern__patternType__bitmaps__symbolsInResourceBlock_PR_NOTHING,	/* No components present */
	RRC_RateMatchPattern__patternType__bitmaps__symbolsInResourceBlock_PR_oneSlot,
	RRC_RateMatchPattern__patternType__bitmaps__symbolsInResourceBlock_PR_twoSlots
} RRC_RateMatchPattern__patternType__bitmaps__symbolsInResourceBlock_PR;
typedef enum RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR {
	RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR_NOTHING,	/* No components present */
	RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR_n2,
	RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR_n4,
	RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR_n5,
	RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR_n8,
	RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR_n10,
	RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR_n20,
	RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR_n40
} RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR;
typedef enum RRC_RateMatchPattern__dummy {
	RRC_RateMatchPattern__dummy_dynamic	= 0,
	RRC_RateMatchPattern__dummy_semiStatic	= 1
} e_RRC_RateMatchPattern__dummy;

/* RRC_RateMatchPattern */
typedef struct RRC_RateMatchPattern {
	RRC_RateMatchPatternId_t	 rateMatchPatternId;
	struct RRC_RateMatchPattern__patternType {
		RRC_RateMatchPattern__patternType_PR present;
		union RRC_RateMatchPattern__RRC_patternType_u {
			struct RRC_RateMatchPattern__patternType__bitmaps {
				BIT_STRING_t	 resourceBlocks;
				struct RRC_RateMatchPattern__patternType__bitmaps__symbolsInResourceBlock {
					RRC_RateMatchPattern__patternType__bitmaps__symbolsInResourceBlock_PR present;
					union RRC_RateMatchPattern__RRC_patternType__RRC_bitmaps__RRC_symbolsInResourceBlock_u {
						BIT_STRING_t	 oneSlot;
						BIT_STRING_t	 twoSlots;
					} choice;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} symbolsInResourceBlock;
				struct RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern {
					RRC_RateMatchPattern__patternType__bitmaps__periodicityAndPattern_PR present;
					union RRC_RateMatchPattern__RRC_patternType__RRC_bitmaps__RRC_periodicityAndPattern_u {
						BIT_STRING_t	 n2;
						BIT_STRING_t	 n4;
						BIT_STRING_t	 n5;
						BIT_STRING_t	 n8;
						BIT_STRING_t	 n10;
						BIT_STRING_t	 n20;
						BIT_STRING_t	 n40;
					} choice;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *periodicityAndPattern;
				/*
				 * This type is extensible,
				 * possible extensions are below.
				 */
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *bitmaps;
			RRC_ControlResourceSetId_t	 controlResourceSet;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} patternType;
	RRC_SubcarrierSpacing_t	*subcarrierSpacing;	/* OPTIONAL */
	long	 dummy;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRC_RateMatchPattern_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_dummy_20;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_RRC_RateMatchPattern;
extern asn_SEQUENCE_specifics_t asn_SPC_RRC_RateMatchPattern_specs_1;
extern asn_TYPE_member_t asn_MBR_RRC_RateMatchPattern_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _RRC_RateMatchPattern_H_ */
#include <asn_internal.h>