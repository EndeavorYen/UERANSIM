/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.rrc.asn.core.RRC_Sequence;
import tr.havelsan.ueransim.rrc.asn.sequence_ofs.RRC_UERadioPagingInformation_IEs__supportedBandListNRForPaging;

public class RRC_UERadioPagingInformation_IEs extends RRC_Sequence {

    public RRC_UERadioPagingInformation_IEs__supportedBandListNRForPaging supportedBandListNRForPaging;
    public RRC_UERadioPagingInformation_IEs__nonCriticalExtension nonCriticalExtension;

    @Override
    public String[] getMemberNames() {
        return new String[]{ "supportedBandListNRForPaging","nonCriticalExtension" };
    }

    @Override
    public String[] getMemberIdentifiers() {
        return new String[]{ "supportedBandListNRForPaging","nonCriticalExtension" };
    }

    @Override
    public String getAsnName() {
        return "UERadioPagingInformation-IEs";
    }

    @Override
    public String getXmlTagName() {
        return "UERadioPagingInformation-IEs";
    }

}
