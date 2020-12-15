/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.app.link.rlc.pdu;

import tr.havelsan.ueransim.app.link.rlc.enums.ESegmentInfo;
import tr.havelsan.ueransim.utils.OctetInputStream;
import tr.havelsan.ueransim.utils.octets.OctetString;

public class AmdPdu {
    public boolean dc;
    public boolean p;
    public ESegmentInfo si;
    public int sn;
    public int so;
    public OctetString data;

    // Indicates whether this SDU is delivered.
    //  If the SDU has fragmentation, ALL AmdPdu which has the same underlying SDU must be
    //  marked as _isDelivered=true at the reassembling and delivering operation.
    public boolean _isProcessed;

    public static AmdPdu decode(OctetInputStream stream, boolean isShortSn) {
        var pdu = new AmdPdu();

        var octet = stream.readOctet();
        pdu.dc = octet.getBitB(7);
        pdu.p = octet.getBitB(6);
        pdu.si = ESegmentInfo.fromSi(octet.getBitRangeI(4, 5));
        pdu.sn = isShortSn ? octet.getBitRangeI(0, 3) : octet.getBitRangeI(0, 1);

        pdu.sn <<= 8;
        pdu.sn |= stream.readOctetI();
        if (!isShortSn) {
            pdu.sn <<= 8;
            pdu.sn |= stream.readOctetI();
        }

        if (pdu.si.requiresSo()) {
            pdu.so = stream.readOctet2I();
        }

        pdu.data = stream.readOctetString();
        return pdu;
    }
}
