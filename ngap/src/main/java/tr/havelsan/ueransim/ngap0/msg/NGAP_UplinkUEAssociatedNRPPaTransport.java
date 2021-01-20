/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.ngap0.msg;

import tr.havelsan.ueransim.ngap0.NgapMessageType;
import tr.havelsan.ueransim.ngap0.NgapProtocolIeType;
import tr.havelsan.ueransim.ngap0.core.NGAP_BaseMessage;
import tr.havelsan.ueransim.ngap0.core.NGAP_Value;
import tr.havelsan.ueransim.ngap0.ies.integers.NGAP_AMF_UE_NGAP_ID;
import tr.havelsan.ueransim.ngap0.ies.integers.NGAP_RAN_UE_NGAP_ID;
import tr.havelsan.ueransim.ngap0.ies.octet_strings.NGAP_NRPPa_PDU;
import tr.havelsan.ueransim.ngap0.ies.octet_strings.NGAP_RoutingID;

public class NGAP_UplinkUEAssociatedNRPPaTransport extends NGAP_BaseMessage {

    public NGAP_UplinkUEAssociatedNRPPaTransport() {

    }

    @Override
    public NgapMessageType getMessageType() {
        return NgapMessageType.UplinkUEAssociatedNRPPaTransport;
    }

    @Override
    public NgapProtocolIeType getProtocolIeType() {
        return NgapProtocolIeType.forMessage("UplinkUEAssociatedNRPPaTransport");
    }

    @Override
    public int getCriticality() {
        return 1;
    }

    @Override
    public int getProcedureCode() {
        return 50;
    }

    @Override
    public int getPduType() {
        return 0;
    }

    @Override
    public int[] getIeId() {
        return new int[] { 10, 85, 89, 46 };
    }

    @Override
    public int[] getIeCriticality() {
        return new int[] { 0, 0, 0, 0 };
    }

    @Override
    public Class<? extends NGAP_Value>[] getIeTypes() {
        return new Class[] { NGAP_AMF_UE_NGAP_ID.class, NGAP_RAN_UE_NGAP_ID.class, NGAP_RoutingID.class, NGAP_NRPPa_PDU.class };
    }

    @Override
    public int[] getIePresence() {
        return new int[] { 2, 2, 2, 2 };
    }

    @Override
    public String[] getMemberIdentifiers() {
        return new String[] { "protocolIEs" };
    }

    @Override
    public String[] getMemberNames() {
        return new String[] { "protocolIEs" };
    }

    @Override
    public String getAsnName() {
        return "UplinkUEAssociatedNRPPaTransport";
    }

    @Override
    public String getXmlTagName() {
        return "UplinkUEAssociatedNRPPaTransport";
    }

}
