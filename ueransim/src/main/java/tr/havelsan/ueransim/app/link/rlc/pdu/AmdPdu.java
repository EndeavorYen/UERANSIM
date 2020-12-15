/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.app.link.rlc.pdu;

import tr.havelsan.ueransim.app.link.rlc.RlcConstants;
import tr.havelsan.ueransim.utils.OctetInputStream;
import tr.havelsan.ueransim.utils.octets.OctetString;

public class AmdPdu {
    public boolean dc;
    public boolean p;
    public int si;
    public int sn;
    public int so;
    public OctetString data;

    public static AmdPdu decode(OctetInputStream stream, boolean isShortSn) {
        var pdu = new AmdPdu();

        var octet = stream.readOctet();
        pdu.dc = octet.getBitB(7);
        pdu.p = octet.getBitB(6);
        pdu.si = octet.getBitRangeI(4, 5);
        pdu.sn = isShortSn ? octet.getBitRangeI(0, 3) : octet.getBitRangeI(0, 1);

        pdu.sn <<= 8;
        pdu.sn |= stream.readOctetI();
        if (!isShortSn) {
            pdu.sn <<= 8;
            pdu.sn |= stream.readOctetI();
        }

        if (pdu.si != RlcConstants.SI_FIRST) {
            pdu.so = stream.readOctet2I();
        }

        pdu.data = stream.readOctetString();
        return pdu;
    }
}
