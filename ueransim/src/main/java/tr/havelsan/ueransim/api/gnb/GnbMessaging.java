/*
 * MIT License
 *
 * Copyright (c) 2020 ALİ GÜNGÖR
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @author Ali Güngör (aligng1620@gmail.com)
 */

package tr.havelsan.ueransim.api.gnb;

import tr.havelsan.ueransim.Ngap;
import tr.havelsan.ueransim.core.GnbSimContext;
import tr.havelsan.ueransim.core.UeSimContext;
import tr.havelsan.ueransim.nas.core.messages.NasMessage;
import tr.havelsan.ueransim.ngap.ngap_ies.AMF_UE_NGAP_ID;
import tr.havelsan.ueransim.ngap.ngap_pdu_contents.DownlinkNASTransport;
import tr.havelsan.ueransim.ngap.ngap_pdu_contents.InitialContextSetupRequest;
import tr.havelsan.ueransim.ngap.ngap_pdu_contents.NGSetupResponse;
import tr.havelsan.ueransim.ngap.ngap_pdu_descriptions.NGAP_PDU;
import tr.havelsan.ueransim.ngap2.NgapBuilder;
import tr.havelsan.ueransim.ngap2.NgapCriticality;
import tr.havelsan.ueransim.ngap2.NgapInternal;
import tr.havelsan.ueransim.ngap2.NgapProcedure;
import tr.havelsan.ueransim.utils.FlowLogging;

public class GnbMessaging {

    public static void sendFromUe(GnbSimContext gnbCtx, UeSimContext ueCtx, NasMessage nasMessage) {
        GnbMessaging.sendToNetwork(gnbCtx, new NgapBuilder(NgapProcedure.UplinkNASTransport, NgapCriticality.IGNORE), nasMessage);
    }

    public static void sendToNetwork(GnbSimContext ctx, NgapBuilder ngapBuilder, NasMessage nasMessage) {
        // Adding NAS PDU (if any)
        if (nasMessage != null) {
            // NOTE: criticality is hardcoded here, it may be changed
            ngapBuilder.addNasPdu(nasMessage, NgapCriticality.REJECT);
        }

        // Adding AMF-UE-NGAP-ID (if any)
        {
            Long amfUeNgapId = ctx.amfUeNgapId;
            if (amfUeNgapId != null) {
                // NOTE: criticality is hardcoded here, it may be changed
                ngapBuilder.addAmfUeNgapId(amfUeNgapId, NgapCriticality.IGNORE);
            }
        }

        // Adding RAN-UE-NGAP-ID
        {
            // NOTE: criticality is hardcoded here, it may be changed
            ngapBuilder.addRanUeNgapId(ctx.ranUeNgapId, NgapCriticality.REJECT);
        }

        // Adding user location information
        {
            // NOTE: criticality is hardcoded here, it may be changed
            ngapBuilder.addUserLocationInformationNR(ctx.simCtx.ue.ueConfig.userLocationInformationNr, NgapCriticality.IGNORE);
        }

        var ngapPdu = ngapBuilder.build();

        FlowLogging.logSendingMessage(ngapPdu);
        ctx.sctpClient.send(ctx.streamNumber, Ngap.perEncode(ngapPdu));
        FlowLogging.logSentMessage();
    }

    public static void receiveFromNetwork(GnbSimContext ctx, NGAP_PDU ngapPdu) {
        var ngapMessage = NgapInternal.extractNgapMessage(ngapPdu);

        // check for AMF-UE-NGAP-ID
        {
            var ieAmfUeNgapId = NgapInternal.extractProtocolIe(ngapMessage, AMF_UE_NGAP_ID.class);
            if (ieAmfUeNgapId.size() > 0) {
                var ie = ieAmfUeNgapId.get(ieAmfUeNgapId.size() - 1);
                ctx.amfUeNgapId = ie.value;
            }
        }

        if (ngapMessage instanceof NGSetupResponse) {
            GnbInterfaceManagement.handleNgSetupResponse(ctx, (NGSetupResponse) ngapMessage);
        } else if (ngapMessage instanceof DownlinkNASTransport) {
            GnbNasTransport.handleDownlinkNasTransport(ctx, (DownlinkNASTransport) ngapMessage);
        } else if (ngapMessage instanceof InitialContextSetupRequest) {
            GnbUeContextManagement.handleInitialContextSetup(ctx, (InitialContextSetupRequest) ngapMessage);
        } else {
            FlowLogging.logUnhandledMessage(ngapMessage.getClass().getSimpleName());
        }
    }
}
