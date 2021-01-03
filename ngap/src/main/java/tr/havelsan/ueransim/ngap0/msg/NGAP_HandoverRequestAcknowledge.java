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
import tr.havelsan.ueransim.ngap0.ies.octet_strings.NGAP_TargetToSource_TransparentContainer;
import tr.havelsan.ueransim.ngap0.ies.sequence_ofs.NGAP_PDUSessionResourceAdmittedList;
import tr.havelsan.ueransim.ngap0.ies.sequence_ofs.NGAP_PDUSessionResourceFailedToSetupListHOAck;
import tr.havelsan.ueransim.ngap0.ies.sequences.NGAP_CriticalityDiagnostics;

public class NGAP_HandoverRequestAcknowledge extends NGAP_BaseMessage {

    public NGAP_HandoverRequestAcknowledge() {

    }

    @Override
    public NgapMessageType getMessageType() {
        return NgapMessageType.HandoverRequestAcknowledge;
    }

    @Override
    public NgapProtocolIeType getProtocolIeType() {
        return NgapProtocolIeType.forMessage("HandoverRequestAcknowledge");
    }

    @Override
    public int getCriticality() {
        return 0;
    }

    @Override
    public int getProcedureCode() {
        return 13;
    }

    @Override
    public int getPduType() {
        return 1;
    }

    @Override
    public int[] getIeId() {
        return new int[] { 10, 85, 53, 56, 106, 19 };
    }

    @Override
    public int[] getIeCriticality() {
        return new int[] { 1, 1, 1, 1, 0, 1 };
    }

    @Override
    public Class<? extends NGAP_Value>[] getIeTypes() {
        return new Class[] { NGAP_AMF_UE_NGAP_ID.class, NGAP_RAN_UE_NGAP_ID.class, NGAP_PDUSessionResourceAdmittedList.class, NGAP_PDUSessionResourceFailedToSetupListHOAck.class, NGAP_TargetToSource_TransparentContainer.class, NGAP_CriticalityDiagnostics.class };
    }

    @Override
    public int[] getIePresence() {
        return new int[] { 2, 2, 2, 0, 2, 0 };
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
        return "HandoverRequestAcknowledge";
    }

    @Override
    public String getXmlTagName() {
        return "HandoverRequestAcknowledge";
    }

}
