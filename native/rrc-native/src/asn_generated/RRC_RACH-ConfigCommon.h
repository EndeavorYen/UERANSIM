/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#ifndef	_RRC_RACH_ConfigCommon_H_
#define	_RRC_RACH_ConfigCommon_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RRC_RACH-ConfigGeneric.h"
#include <NativeInteger.h>
#include <NativeEnumerated.h>
#include "RRC_RSRP-Range.h"
#include "RRC_SubcarrierSpacing.h"
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR {
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_NOTHING,	/* No components present */
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneEighth,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneFourth,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneHalf,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_one,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_two,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_four,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_eight,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_sixteen
} RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR;
typedef enum RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth {
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n4	= 0,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n8	= 1,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n12	= 2,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n16	= 3,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n20	= 4,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n24	= 5,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n28	= 6,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n32	= 7,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n36	= 8,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n40	= 9,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n44	= 10,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n48	= 11,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n52	= 12,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n56	= 13,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n60	= 14,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n64	= 15
} e_RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth;
typedef enum RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth {
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n4	= 0,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n8	= 1,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n12	= 2,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n16	= 3,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n20	= 4,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n24	= 5,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n28	= 6,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n32	= 7,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n36	= 8,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n40	= 9,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n44	= 10,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n48	= 11,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n52	= 12,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n56	= 13,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n60	= 14,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n64	= 15
} e_RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth;
typedef enum RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf {
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n4	= 0,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n8	= 1,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n12	= 2,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n16	= 3,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n20	= 4,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n24	= 5,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n28	= 6,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n32	= 7,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n36	= 8,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n40	= 9,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n44	= 10,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n48	= 11,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n52	= 12,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n56	= 13,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n60	= 14,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n64	= 15
} e_RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf;
typedef enum RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one {
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n4	= 0,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n8	= 1,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n12	= 2,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n16	= 3,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n20	= 4,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n24	= 5,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n28	= 6,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n32	= 7,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n36	= 8,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n40	= 9,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n44	= 10,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n48	= 11,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n52	= 12,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n56	= 13,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n60	= 14,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n64	= 15
} e_RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one;
typedef enum RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two {
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n4	= 0,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n8	= 1,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n12	= 2,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n16	= 3,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n20	= 4,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n24	= 5,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n28	= 6,
	RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n32	= 7
} e_RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two;
typedef enum RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA {
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b56	= 0,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b144	= 1,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b208	= 2,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b256	= 3,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b282	= 4,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b480	= 5,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b640	= 6,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b800	= 7,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b1000	= 8,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b72	= 9,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare6	= 10,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare5	= 11,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare4	= 12,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare3	= 13,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare2	= 14,
	RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare1	= 15
} e_RRC_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA;
typedef enum RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB {
	RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_minusinfinity	= 0,
	RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB0	= 1,
	RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB5	= 2,
	RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB8	= 3,
	RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB10	= 4,
	RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB12	= 5,
	RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB15	= 6,
	RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB18	= 7
} e_RRC_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB;
typedef enum RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer {
	RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer_sf8	= 0,
	RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer_sf16	= 1,
	RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer_sf24	= 2,
	RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer_sf32	= 3,
	RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer_sf40	= 4,
	RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer_sf48	= 5,
	RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer_sf56	= 6,
	RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer_sf64	= 7
} e_RRC_RACH_ConfigCommon__ra_ContentionResolutionTimer;
typedef enum RRC_RACH_ConfigCommon__prach_RootSequenceIndex_PR {
	RRC_RACH_ConfigCommon__prach_RootSequenceIndex_PR_NOTHING,	/* No components present */
	RRC_RACH_ConfigCommon__prach_RootSequenceIndex_PR_l839,
	RRC_RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139
} RRC_RACH_ConfigCommon__prach_RootSequenceIndex_PR;
typedef enum RRC_RACH_ConfigCommon__restrictedSetConfig {
	RRC_RACH_ConfigCommon__restrictedSetConfig_unrestrictedSet	= 0,
	RRC_RACH_ConfigCommon__restrictedSetConfig_restrictedSetTypeA	= 1,
	RRC_RACH_ConfigCommon__restrictedSetConfig_restrictedSetTypeB	= 2
} e_RRC_RACH_ConfigCommon__restrictedSetConfig;
typedef enum RRC_RACH_ConfigCommon__msg3_transformPrecoder {
	RRC_RACH_ConfigCommon__msg3_transformPrecoder_enabled	= 0
} e_RRC_RACH_ConfigCommon__msg3_transformPrecoder;

/* RRC_RACH-ConfigCommon */
typedef struct RRC_RACH_ConfigCommon {
	RRC_RACH_ConfigGeneric_t	 rach_ConfigGeneric;
	long	*totalNumberOfRA_Preambles;	/* OPTIONAL */
	struct RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB {
		RRC_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR present;
		union RRC_RACH_ConfigCommon__RRC_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_u {
			long	 oneEighth;
			long	 oneFourth;
			long	 oneHalf;
			long	 one;
			long	 two;
			long	 four;
			long	 eight;
			long	 sixteen;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ssb_perRACH_OccasionAndCB_PreamblesPerSSB;
	struct RRC_RACH_ConfigCommon__groupBconfigured {
		long	 ra_Msg3SizeGroupA;
		long	 messagePowerOffsetGroupB;
		long	 numberOfRA_PreamblesGroupA;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *groupBconfigured;
	long	 ra_ContentionResolutionTimer;
	RRC_RSRP_Range_t	*rsrp_ThresholdSSB;	/* OPTIONAL */
	RRC_RSRP_Range_t	*rsrp_ThresholdSSB_SUL;	/* OPTIONAL */
	struct RRC_RACH_ConfigCommon__prach_RootSequenceIndex {
		RRC_RACH_ConfigCommon__prach_RootSequenceIndex_PR present;
		union RRC_RACH_ConfigCommon__RRC_prach_RootSequenceIndex_u {
			long	 l839;
			long	 l139;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} prach_RootSequenceIndex;
	RRC_SubcarrierSpacing_t	*msg1_SubcarrierSpacing;	/* OPTIONAL */
	long	 restrictedSetConfig;
	long	*msg3_transformPrecoder;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRC_RACH_ConfigCommon_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_oneEighth_5;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_oneFourth_22;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_oneHalf_39;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_one_56;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_two_73;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_ra_Msg3SizeGroupA_86;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_messagePowerOffsetGroupB_103;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_ra_ContentionResolutionTimer_113;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_restrictedSetConfig_128;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_msg3_transformPrecoder_132;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_RRC_RACH_ConfigCommon;
extern asn_SEQUENCE_specifics_t asn_SPC_RRC_RACH_ConfigCommon_specs_1;
extern asn_TYPE_member_t asn_MBR_RRC_RACH_ConfigCommon_1[11];

#ifdef __cplusplus
}
#endif

#endif	/* _RRC_RACH_ConfigCommon_H_ */
#include <asn_internal.h>