/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.rrc.asn.sequence_ofs;

import tr.havelsan.ueransim.rrc.asn.core.RRC_SequenceOf;
import tr.havelsan.ueransim.rrc.asn.sequences.RRC_MeasResult2NR;

public class RRC_MeasResultList2NR extends RRC_SequenceOf<RRC_MeasResult2NR> {

    @Override
    public String getAsnName() {
        return "MeasResultList2NR";
    }

    @Override
    public String getXmlTagName() {
        return "MeasResultList2NR";
    }

    @Override
    public Class<RRC_MeasResult2NR> getItemType() {
        return RRC_MeasResult2NR.class;
    }

}
