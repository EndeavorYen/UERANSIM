/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#include "ASN_RRC_RF-Parameters.h"

#include "ASN_RRC_BandCombinationList.h"
#include "ASN_RRC_FreqBandList.h"
#include "ASN_RRC_BandNR.h"
#include "ASN_RRC_BandCombinationList-v1540.h"
#include "ASN_RRC_BandCombinationList-v1550.h"
#include "ASN_RRC_BandCombinationList-v1560.h"
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static int
memb_ASN_RRC_supportedBandListNR_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	/* Determine the number of elements */
	size = _A_CSEQUENCE_FROM_VOID(sptr)->count;
	
	if((size >= 1 && size <= 1024)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_ASN_RRC_supportedBandListNR_constr_2 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 10,  10,  1,  1024 }	/* (SIZE(1..1024)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_ASN_RRC_srs_SwitchingTimeRequested_constr_9 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_ASN_RRC_supportedBandListNR_constr_2 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 10,  10,  1,  1024 }	/* (SIZE(1..1024)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_ASN_RRC_supportedBandListNR_2[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_ASN_RRC_BandNR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_ASN_RRC_supportedBandListNR_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_ASN_RRC_supportedBandListNR_specs_2 = {
	sizeof(struct ASN_RRC_RF_Parameters__supportedBandListNR),
	offsetof(struct ASN_RRC_RF_Parameters__supportedBandListNR, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ASN_RRC_supportedBandListNR_2 = {
	"supportedBandListNR",
	"supportedBandListNR",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_ASN_RRC_supportedBandListNR_tags_2,
	sizeof(asn_DEF_ASN_RRC_supportedBandListNR_tags_2)
		/sizeof(asn_DEF_ASN_RRC_supportedBandListNR_tags_2[0]) - 1, /* 1 */
	asn_DEF_ASN_RRC_supportedBandListNR_tags_2,	/* Same as above */
	sizeof(asn_DEF_ASN_RRC_supportedBandListNR_tags_2)
		/sizeof(asn_DEF_ASN_RRC_supportedBandListNR_tags_2[0]), /* 2 */
	{ 0, &asn_PER_type_ASN_RRC_supportedBandListNR_constr_2, SEQUENCE_OF_constraint },
	asn_MBR_ASN_RRC_supportedBandListNR_2,
	1,	/* Single element */
	&asn_SPC_ASN_RRC_supportedBandListNR_specs_2	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_ASN_RRC_srs_SwitchingTimeRequested_value2enum_9[] = {
	{ 0,	4,	"true" }
};
static const unsigned int asn_MAP_ASN_RRC_srs_SwitchingTimeRequested_enum2value_9[] = {
	0	/* true(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_ASN_RRC_srs_SwitchingTimeRequested_specs_9 = {
	asn_MAP_ASN_RRC_srs_SwitchingTimeRequested_value2enum_9,	/* "tag" => N; sorted by tag */
	asn_MAP_ASN_RRC_srs_SwitchingTimeRequested_enum2value_9,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_9 = {
	"srs-SwitchingTimeRequested",
	"srs-SwitchingTimeRequested",
	&asn_OP_NativeEnumerated,
	asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_tags_9,
	sizeof(asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_tags_9)
		/sizeof(asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_tags_9[0]) - 1, /* 1 */
	asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_tags_9,	/* Same as above */
	sizeof(asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_tags_9)
		/sizeof(asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_tags_9[0]), /* 2 */
	{ 0, &asn_PER_type_ASN_RRC_srs_SwitchingTimeRequested_constr_9, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_ASN_RRC_srs_SwitchingTimeRequested_specs_9	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ASN_RRC_ext1_7[] = {
	{ ATF_POINTER, 2, offsetof(struct ASN_RRC_RF_Parameters__ext1, supportedBandCombinationList_v1540),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_RRC_BandCombinationList_v1540,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"supportedBandCombinationList-v1540"
		},
	{ ATF_POINTER, 1, offsetof(struct ASN_RRC_RF_Parameters__ext1, srs_SwitchingTimeRequested),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_RRC_srs_SwitchingTimeRequested_9,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"srs-SwitchingTimeRequested"
		},
};
static const int asn_MAP_ASN_RRC_ext1_oms_7[] = { 0, 1 };
static const ber_tlv_tag_t asn_DEF_ASN_RRC_ext1_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ASN_RRC_ext1_tag2el_7[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* supportedBandCombinationList-v1540 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* srs-SwitchingTimeRequested */
};
static asn_SEQUENCE_specifics_t asn_SPC_ASN_RRC_ext1_specs_7 = {
	sizeof(struct ASN_RRC_RF_Parameters__ext1),
	offsetof(struct ASN_RRC_RF_Parameters__ext1, _asn_ctx),
	asn_MAP_ASN_RRC_ext1_tag2el_7,
	2,	/* Count of tags in the map */
	asn_MAP_ASN_RRC_ext1_oms_7,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ASN_RRC_ext1_7 = {
	"ext1",
	"ext1",
	&asn_OP_SEQUENCE,
	asn_DEF_ASN_RRC_ext1_tags_7,
	sizeof(asn_DEF_ASN_RRC_ext1_tags_7)
		/sizeof(asn_DEF_ASN_RRC_ext1_tags_7[0]) - 1, /* 1 */
	asn_DEF_ASN_RRC_ext1_tags_7,	/* Same as above */
	sizeof(asn_DEF_ASN_RRC_ext1_tags_7)
		/sizeof(asn_DEF_ASN_RRC_ext1_tags_7[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ASN_RRC_ext1_7,
	2,	/* Elements count */
	&asn_SPC_ASN_RRC_ext1_specs_7	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ASN_RRC_ext2_11[] = {
	{ ATF_POINTER, 1, offsetof(struct ASN_RRC_RF_Parameters__ext2, supportedBandCombinationList_v1550),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_RRC_BandCombinationList_v1550,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"supportedBandCombinationList-v1550"
		},
};
static const int asn_MAP_ASN_RRC_ext2_oms_11[] = { 0 };
static const ber_tlv_tag_t asn_DEF_ASN_RRC_ext2_tags_11[] = {
	(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ASN_RRC_ext2_tag2el_11[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* supportedBandCombinationList-v1550 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ASN_RRC_ext2_specs_11 = {
	sizeof(struct ASN_RRC_RF_Parameters__ext2),
	offsetof(struct ASN_RRC_RF_Parameters__ext2, _asn_ctx),
	asn_MAP_ASN_RRC_ext2_tag2el_11,
	1,	/* Count of tags in the map */
	asn_MAP_ASN_RRC_ext2_oms_11,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ASN_RRC_ext2_11 = {
	"ext2",
	"ext2",
	&asn_OP_SEQUENCE,
	asn_DEF_ASN_RRC_ext2_tags_11,
	sizeof(asn_DEF_ASN_RRC_ext2_tags_11)
		/sizeof(asn_DEF_ASN_RRC_ext2_tags_11[0]) - 1, /* 1 */
	asn_DEF_ASN_RRC_ext2_tags_11,	/* Same as above */
	sizeof(asn_DEF_ASN_RRC_ext2_tags_11)
		/sizeof(asn_DEF_ASN_RRC_ext2_tags_11[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ASN_RRC_ext2_11,
	1,	/* Elements count */
	&asn_SPC_ASN_RRC_ext2_specs_11	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ASN_RRC_ext3_13[] = {
	{ ATF_POINTER, 1, offsetof(struct ASN_RRC_RF_Parameters__ext3, supportedBandCombinationList_v1560),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_RRC_BandCombinationList_v1560,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"supportedBandCombinationList-v1560"
		},
};
static const int asn_MAP_ASN_RRC_ext3_oms_13[] = { 0 };
static const ber_tlv_tag_t asn_DEF_ASN_RRC_ext3_tags_13[] = {
	(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ASN_RRC_ext3_tag2el_13[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* supportedBandCombinationList-v1560 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ASN_RRC_ext3_specs_13 = {
	sizeof(struct ASN_RRC_RF_Parameters__ext3),
	offsetof(struct ASN_RRC_RF_Parameters__ext3, _asn_ctx),
	asn_MAP_ASN_RRC_ext3_tag2el_13,
	1,	/* Count of tags in the map */
	asn_MAP_ASN_RRC_ext3_oms_13,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ASN_RRC_ext3_13 = {
	"ext3",
	"ext3",
	&asn_OP_SEQUENCE,
	asn_DEF_ASN_RRC_ext3_tags_13,
	sizeof(asn_DEF_ASN_RRC_ext3_tags_13)
		/sizeof(asn_DEF_ASN_RRC_ext3_tags_13[0]) - 1, /* 1 */
	asn_DEF_ASN_RRC_ext3_tags_13,	/* Same as above */
	sizeof(asn_DEF_ASN_RRC_ext3_tags_13)
		/sizeof(asn_DEF_ASN_RRC_ext3_tags_13[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ASN_RRC_ext3_13,
	1,	/* Elements count */
	&asn_SPC_ASN_RRC_ext3_specs_13	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_ASN_RRC_RF_Parameters_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ASN_RRC_RF_Parameters, supportedBandListNR),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_ASN_RRC_supportedBandListNR_2,
		0,
		{ 0, &asn_PER_memb_ASN_RRC_supportedBandListNR_constr_2,  memb_ASN_RRC_supportedBandListNR_constraint_1 },
		0, 0, /* No default value */
		"supportedBandListNR"
		},
	{ ATF_POINTER, 5, offsetof(struct ASN_RRC_RF_Parameters, supportedBandCombinationList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_RRC_BandCombinationList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"supportedBandCombinationList"
		},
	{ ATF_POINTER, 4, offsetof(struct ASN_RRC_RF_Parameters, appliedFreqBandListFilter),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_RRC_FreqBandList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"appliedFreqBandListFilter"
		},
	{ ATF_POINTER, 3, offsetof(struct ASN_RRC_RF_Parameters, ext1),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		0,
		&asn_DEF_ASN_RRC_ext1_7,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ext1"
		},
	{ ATF_POINTER, 2, offsetof(struct ASN_RRC_RF_Parameters, ext2),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		0,
		&asn_DEF_ASN_RRC_ext2_11,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ext2"
		},
	{ ATF_POINTER, 1, offsetof(struct ASN_RRC_RF_Parameters, ext3),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		0,
		&asn_DEF_ASN_RRC_ext3_13,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ext3"
		},
};
static const int asn_MAP_ASN_RRC_RF_Parameters_oms_1[] = { 1, 2, 3, 4, 5 };
static const ber_tlv_tag_t asn_DEF_ASN_RRC_RF_Parameters_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ASN_RRC_RF_Parameters_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* supportedBandListNR */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* supportedBandCombinationList */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* appliedFreqBandListFilter */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* ext1 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* ext2 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* ext3 */
};
asn_SEQUENCE_specifics_t asn_SPC_ASN_RRC_RF_Parameters_specs_1 = {
	sizeof(struct ASN_RRC_RF_Parameters),
	offsetof(struct ASN_RRC_RF_Parameters, _asn_ctx),
	asn_MAP_ASN_RRC_RF_Parameters_tag2el_1,
	6,	/* Count of tags in the map */
	asn_MAP_ASN_RRC_RF_Parameters_oms_1,	/* Optional members */
	2, 3,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ASN_RRC_RF_Parameters = {
	"RF-Parameters",
	"RF-Parameters",
	&asn_OP_SEQUENCE,
	asn_DEF_ASN_RRC_RF_Parameters_tags_1,
	sizeof(asn_DEF_ASN_RRC_RF_Parameters_tags_1)
		/sizeof(asn_DEF_ASN_RRC_RF_Parameters_tags_1[0]), /* 1 */
	asn_DEF_ASN_RRC_RF_Parameters_tags_1,	/* Same as above */
	sizeof(asn_DEF_ASN_RRC_RF_Parameters_tags_1)
		/sizeof(asn_DEF_ASN_RRC_RF_Parameters_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ASN_RRC_RF_Parameters_1,
	6,	/* Elements count */
	&asn_SPC_ASN_RRC_RF_Parameters_specs_1	/* Additional specs */
};

