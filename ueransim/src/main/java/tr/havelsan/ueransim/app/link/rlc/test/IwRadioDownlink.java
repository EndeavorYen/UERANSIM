/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.app.link.rlc.test;

import tr.havelsan.ueransim.utils.octets.OctetString;

class IwRadioDownlink {
    public final OctetString data;

    public IwRadioDownlink(OctetString data) {
        this.data = data;
    }
}
