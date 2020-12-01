/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.rrc.asn.core.RRC_Sequence;

public class RRC_UE_MRDC_CapabilityAddXDD_Mode_v1560 extends RRC_Sequence {

    public RRC_MeasAndMobParametersMRDC_XDD_Diff_v1560 measAndMobParametersMRDC_XDD_Diff_v1560;

    @Override
    public String[] getMemberNames() {
        return new String[]{ "measAndMobParametersMRDC-XDD-Diff-v1560" };
    }

    @Override
    public String[] getMemberIdentifiers() {
        return new String[]{ "measAndMobParametersMRDC_XDD_Diff_v1560" };
    }

    @Override
    public String getAsnName() {
        return "UE-MRDC-CapabilityAddXDD-Mode-v1560";
    }

    @Override
    public String getXmlTagName() {
        return "UE-MRDC-CapabilityAddXDD-Mode-v1560";
    }

}
