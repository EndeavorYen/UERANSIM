/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.rrc.asn.choices.RRC_CSI_ReportConfig__reportFreqConfiguration__csi_ReportingBand;
import tr.havelsan.ueransim.rrc.asn.core.RRC_Integer;
import tr.havelsan.ueransim.rrc.asn.core.RRC_Sequence;

public class RRC_CSI_ReportConfig__reportFreqConfiguration extends RRC_Sequence {

    public RRC_Integer cqi_FormatIndicator;
    public RRC_Integer pmi_FormatIndicator;
    public RRC_CSI_ReportConfig__reportFreqConfiguration__csi_ReportingBand csi_ReportingBand;

    @Override
    public String[] getMemberNames() {
        return new String[]{ "cqi-FormatIndicator","pmi-FormatIndicator","csi-ReportingBand" };
    }

    @Override
    public String[] getMemberIdentifiers() {
        return new String[]{ "cqi_FormatIndicator","pmi_FormatIndicator","csi_ReportingBand" };
    }

    @Override
    public String getAsnName() {
        throw new IllegalStateException("ASN.1 name is treated null for anonymous types.");
    }

    @Override
    public String getXmlTagName() {
        throw new IllegalStateException("XML tag name is treated null for anonymous types.");
    }

}
