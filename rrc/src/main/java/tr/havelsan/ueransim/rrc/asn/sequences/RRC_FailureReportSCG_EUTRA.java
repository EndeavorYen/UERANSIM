/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.rrc.asn.core.RRC_Integer;
import tr.havelsan.ueransim.rrc.asn.core.RRC_OctetString;
import tr.havelsan.ueransim.rrc.asn.core.RRC_Sequence;
import tr.havelsan.ueransim.rrc.asn.sequence_ofs.RRC_MeasResultFreqListFailMRDC;

public class RRC_FailureReportSCG_EUTRA extends RRC_Sequence {

    public RRC_Integer failureType;
    public RRC_MeasResultFreqListFailMRDC measResultFreqListMRDC;
    public RRC_OctetString measResultSCG_FailureMRDC;

    @Override
    public String[] getMemberNames() {
        return new String[]{ "failureType","measResultFreqListMRDC","measResultSCG-FailureMRDC" };
    }

    @Override
    public String[] getMemberIdentifiers() {
        return new String[]{ "failureType","measResultFreqListMRDC","measResultSCG_FailureMRDC" };
    }

    @Override
    public String getAsnName() {
        return "FailureReportSCG-EUTRA";
    }

    @Override
    public String getXmlTagName() {
        return "FailureReportSCG-EUTRA";
    }

}
