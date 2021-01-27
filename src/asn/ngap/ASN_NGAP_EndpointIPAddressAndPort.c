/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NGAP-IEs"
 * 	found in "asn/ngap-15.8.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D ngap`
 */

#include "ASN_NGAP_EndpointIPAddressAndPort.h"

#include "ASN_NGAP_ProtocolExtensionContainer.h"
asn_TYPE_member_t asn_MBR_ASN_NGAP_EndpointIPAddressAndPort_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ASN_NGAP_EndpointIPAddressAndPort, endpointIPAddress),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_NGAP_TransportLayerAddress,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"endpointIPAddress"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ASN_NGAP_EndpointIPAddressAndPort, portNumber),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_NGAP_PortNumber,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"portNumber"
		},
	{ ATF_POINTER, 1, offsetof(struct ASN_NGAP_EndpointIPAddressAndPort, iE_Extensions),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_NGAP_ProtocolExtensionContainer_6861P49,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"iE-Extensions"
		},
};
static const int asn_MAP_ASN_NGAP_EndpointIPAddressAndPort_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_ASN_NGAP_EndpointIPAddressAndPort_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ASN_NGAP_EndpointIPAddressAndPort_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* endpointIPAddress */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* portNumber */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* iE-Extensions */
};
asn_SEQUENCE_specifics_t asn_SPC_ASN_NGAP_EndpointIPAddressAndPort_specs_1 = {
	sizeof(struct ASN_NGAP_EndpointIPAddressAndPort),
	offsetof(struct ASN_NGAP_EndpointIPAddressAndPort, _asn_ctx),
	asn_MAP_ASN_NGAP_EndpointIPAddressAndPort_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_ASN_NGAP_EndpointIPAddressAndPort_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ASN_NGAP_EndpointIPAddressAndPort = {
	"EndpointIPAddressAndPort",
	"EndpointIPAddressAndPort",
	&asn_OP_SEQUENCE,
	asn_DEF_ASN_NGAP_EndpointIPAddressAndPort_tags_1,
	sizeof(asn_DEF_ASN_NGAP_EndpointIPAddressAndPort_tags_1)
		/sizeof(asn_DEF_ASN_NGAP_EndpointIPAddressAndPort_tags_1[0]), /* 1 */
	asn_DEF_ASN_NGAP_EndpointIPAddressAndPort_tags_1,	/* Same as above */
	sizeof(asn_DEF_ASN_NGAP_EndpointIPAddressAndPort_tags_1)
		/sizeof(asn_DEF_ASN_NGAP_EndpointIPAddressAndPort_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ASN_NGAP_EndpointIPAddressAndPort_1,
	3,	/* Elements count */
	&asn_SPC_ASN_NGAP_EndpointIPAddressAndPort_specs_1	/* Additional specs */
};
