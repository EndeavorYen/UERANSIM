package com.runsim.backend.nas.impl.messages;

import com.runsim.backend.nas.core.IMessageBuilder;
import com.runsim.backend.nas.core.messages.PlainMmMessage;
import com.runsim.backend.nas.impl.enums.EMessageType;
import com.runsim.backend.nas.impl.ies.IEPduSessionStatus;

public class NotificationResponse extends PlainMmMessage {
    public IEPduSessionStatus pduSessionStatus;

    public NotificationResponse() {
        super(EMessageType.NOTIFICATION_RESPONSE);
    }

    public NotificationResponse(IEPduSessionStatus pduSessionStatus) {
        this();
        this.pduSessionStatus = pduSessionStatus;
    }

    @Override
    public void build(IMessageBuilder builder) {
        super.build(builder);

        builder.optionalIE(0x50, "pduSessionStatus");
    }
}
