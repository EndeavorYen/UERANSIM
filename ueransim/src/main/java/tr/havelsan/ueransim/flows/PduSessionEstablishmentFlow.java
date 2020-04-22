package tr.havelsan.ueransim.flows;

import fr.marben.asnsdk.japi.InvalidStructureException;
import fr.marben.asnsdk.japi.spe.ContainingOctetStringValue;
import tr.havelsan.ueransim.BaseFlow;
import tr.havelsan.ueransim.contexts.SimulationContext;
import tr.havelsan.ueransim.flowinputs.PduSessionEstablishmentInput;
import tr.havelsan.ueransim.nas.NasEncoder;
import tr.havelsan.ueransim.nas.impl.enums.EPduSessionIdentity;
import tr.havelsan.ueransim.nas.impl.enums.EPduSessionType;
import tr.havelsan.ueransim.nas.impl.enums.EProcedureTransactionIdentity;
import tr.havelsan.ueransim.nas.impl.ies.*;
import tr.havelsan.ueransim.nas.impl.ies.IEIntegrityProtectionMaximumDataRate.EMaximumDataRatePerUeForUserPlaneIntegrityProtectionForDownlink;
import tr.havelsan.ueransim.nas.impl.ies.IEIntegrityProtectionMaximumDataRate.EMaximumDataRatePerUeForUserPlaneIntegrityProtectionForUplink;
import tr.havelsan.ueransim.nas.impl.ies.IEPayloadContainerType.EPayloadContainerType;
import tr.havelsan.ueransim.nas.impl.ies.IERequestType.ERequestType;
import tr.havelsan.ueransim.nas.impl.ies.IESscMode.ESscMode;
import tr.havelsan.ueransim.nas.impl.messages.PduSessionEstablishmentRequest;
import tr.havelsan.ueransim.nas.impl.messages.UlNasTransport;
import tr.havelsan.ueransim.ngap.ngap_ies.*;
import tr.havelsan.ueransim.ngap.ngap_pdu_contents.PDUSessionResourceSetupRequest;
import tr.havelsan.ueransim.ngap.ngap_pdu_descriptions.InitiatingMessage;
import tr.havelsan.ueransim.ngap.ngap_pdu_descriptions.NGAP_PDU;
import tr.havelsan.ueransim.ngap2.NgapBuilder;
import tr.havelsan.ueransim.ngap2.NgapCriticality;
import tr.havelsan.ueransim.ngap2.NgapPduDescription;
import tr.havelsan.ueransim.ngap2.NgapProcedure;
import tr.havelsan.ueransim.utils.Color;
import tr.havelsan.ueransim.utils.Console;
import tr.havelsan.ueransim.utils.octets.OctetString;

import java.util.Collections;

import static tr.havelsan.ueransim.ngap.Values.NGAP_Constants__id_PDUSessionResourceSetupListSURes;

public class PduSessionEstablishmentFlow extends BaseFlow {

    private final PduSessionEstablishmentInput input;

    public PduSessionEstablishmentFlow(SimulationContext simContext, PduSessionEstablishmentInput input) {
        super(simContext);
        this.input = input;
    }

    @Override
    public State main(NGAP_PDU ngapIn) {
        return sendEstablishmentRequest();
    }

    private State sendEstablishmentRequest() {
        var pduSessionEstablishmentRequest = new PduSessionEstablishmentRequest();
        pduSessionEstablishmentRequest.pduSessionId =
                EPduSessionIdentity.fromValue(input.pduSessionId.intValue());
        pduSessionEstablishmentRequest.pti =
                EProcedureTransactionIdentity.fromValue(input.procedureTransactionId.intValue());
        pduSessionEstablishmentRequest.integrityProtectionMaximumDataRate =
                new IEIntegrityProtectionMaximumDataRate(
                        EMaximumDataRatePerUeForUserPlaneIntegrityProtectionForUplink.FULL_DATA_RATE,
                        EMaximumDataRatePerUeForUserPlaneIntegrityProtectionForDownlink.FULL_DATA_RATE);
        pduSessionEstablishmentRequest.pduSessionType = new IEPduSessionType(EPduSessionType.IPV4);
        pduSessionEstablishmentRequest.sscMode = new IESscMode(ESscMode.SSC_MODE_1);

        var ulNasTransport = new UlNasTransport();
        ulNasTransport.payloadContainerType =
                new IEPayloadContainerType(EPayloadContainerType.N1_SM_INFORMATION);
        ulNasTransport.payloadContainer =
                new IEPayloadContainer(new OctetString(NasEncoder.nasPdu(pduSessionEstablishmentRequest)));
        ulNasTransport.pduSessionId = new IEPduSessionIdentity2(input.pduSessionId);
        ulNasTransport.requestType = new IERequestType(ERequestType.INITIAL_REQUEST);
        ulNasTransport.sNssa = input.sNssai;
        ulNasTransport.dnn = input.dnn;

        var ngap = new NgapBuilder()
                .withDescription(NgapPduDescription.INITIATING_MESSAGE)
                .withProcedure(NgapProcedure.UplinkNASTransport, NgapCriticality.IGNORE)
                .addRanUeNgapId(input.ranUeNgapId, NgapCriticality.REJECT)
                .addAmfUeNgapId(input.amfUeNgapId, NgapCriticality.REJECT)
                .addNasPdu(ulNasTransport, NgapCriticality.REJECT)
                .addUserLocationInformationNR(input.userLocationInformationNr, NgapCriticality.IGNORE)
                .build();
        sendPDU(ngap);

        return this::waitPduSessionEstablishmentAccept;
    }

    private State waitPduSessionEstablishmentAccept(NGAP_PDU ngapIn) {
        logReceivedMessage(ngapIn);

        if (!(ngapIn.getValue() instanceof InitiatingMessage)) {
            Console.println(Color.YELLOW, "bad message, InitiatingMessage is expected. message ignored");
            return this::waitPduSessionEstablishmentAccept;
        }

        var initiatingMessage = (InitiatingMessage) ngapIn.getValue();
        if (!(initiatingMessage.value.getDecodedValue() instanceof PDUSessionResourceSetupRequest)) {
            Console.println(
                    Color.YELLOW, "bad message, PDUSessionResourceSetupRequest is expected. message ignored");
            return this::waitPduSessionEstablishmentAccept;
        }

        return sendPduSessionResourceSetupResponse();
    }

    private State sendPduSessionResourceSetupResponse() {
        var gtpTunnel = new GTPTunnel();
        gtpTunnel.transportLayerAddress = new TransportLayerAddress(input.transportLayerAddress.toByteArray(), 32);
        gtpTunnel.gTP_TEID = new GTP_TEID(input.gTpTeid.toByteArray());

        var transfer = new PDUSessionResourceSetupResponseTransfer();
        transfer.qosFlowPerTNLInformation = new QosFlowPerTNLInformation();
        try {
            transfer.qosFlowPerTNLInformation.uPTransportLayerInformation = new UPTransportLayerInformation(UPTransportLayerInformation.ASN_gTPTunnel, gtpTunnel);
        } catch (InvalidStructureException e) {
            throw new RuntimeException(e);
        }
        transfer.qosFlowPerTNLInformation.associatedQosFlowList = new AssociatedQosFlowList();

        var associatedFlowItem = new AssociatedQosFlowItem();
        associatedFlowItem.qosFlowIdentifier = new QosFlowIdentifier(input.qosFlowIdentifier);
        transfer.qosFlowPerTNLInformation.associatedQosFlowList.valueList = Collections.singletonList(associatedFlowItem);

        var list = new PDUSessionResourceSetupListSURes();
        var item = new PDUSessionResourceSetupItemSURes();

        item.pDUSessionID = new PDUSessionID(input.pduSessionId.intValue());
        item.pDUSessionResourceSetupResponseTransfer = new ContainingOctetStringValue(transfer);
        list.valueList = Collections.singletonList(item);

        var ngap = new NgapBuilder()
                .withDescription(NgapPduDescription.SUCCESSFUL_OUTCOME)
                .withProcedure(NgapProcedure.PDUSessionResourceSetupResponse, NgapCriticality.REJECT)
                .addRanUeNgapId(input.ranUeNgapId, NgapCriticality.IGNORE)
                .addAmfUeNgapId(input.amfUeNgapId, NgapCriticality.IGNORE)
                .addProtocolIE(list, NgapCriticality.IGNORE, NGAP_Constants__id_PDUSessionResourceSetupListSURes)
                .build();

        sendPDU(ngap);

        Console.println(Color.GREEN, "PDU Session Establishment Completed");
        return abortReceiver();
    }
}
