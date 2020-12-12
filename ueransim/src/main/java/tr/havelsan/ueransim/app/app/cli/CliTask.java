/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.app.app.cli;

import tr.havelsan.ueransim.app.app.AppConfig;
import tr.havelsan.ueransim.app.app.UeRanSim;
import tr.havelsan.ueransim.app.common.Supi;
import tr.havelsan.ueransim.app.common.cli.*;
import tr.havelsan.ueransim.app.common.configs.UeConfig;
import tr.havelsan.ueransim.app.common.info.UeStatusInfo;
import tr.havelsan.ueransim.app.common.itms.IwCliClientMessage;
import tr.havelsan.ueransim.app.common.itms.IwCliServerMessage;
import tr.havelsan.ueransim.app.common.itms.IwUeStatusInfoRequest;
import tr.havelsan.ueransim.app.ue.app.UeAppTask;
import tr.havelsan.ueransim.app.utils.MtsInitializer;
import tr.havelsan.ueransim.itms.ItmsId;
import tr.havelsan.ueransim.itms.nts.NtsTask;
import tr.havelsan.ueransim.mts.ImplicitTypedObject;
import tr.havelsan.ueransim.mts.MtsContext;
import tr.havelsan.ueransim.utils.Json;
import tr.havelsan.ueransim.utils.Utils;
import tr.havelsan.ueransim.utils.octets.OctetString;

import java.util.ArrayList;
import java.util.UUID;
import java.util.function.Consumer;

public class CliTask extends NtsTask {

    private final AppConfig appConfig;
    private final UeRanSim ueransim;
    private final ServerTask serverTask;

    public CliTask(AppConfig appConfig, UeRanSim ueransim) {
        this.appConfig = appConfig;
        this.ueransim = ueransim;
        this.serverTask = new ServerTask(this);
    }

    @Override
    public void main() {
        serverTask.start();

        while (true) {
            var msg = take();

            if (msg instanceof IwCliClientMessage) {
                var client = ((IwCliClientMessage) msg).client;
                var data = ((IwCliClientMessage) msg).data;

                var cmd = CliUtils.decodeCmdPdu(data, s -> sendCmd(client, new CmdErrorIndication(s)));
                receiveCmd(client, cmd);
            }
        }
    }

    private void sendCmd(UUID client, CmdMessage message) {
        serverTask.push(new IwCliServerMessage(client, CliUtils.encodeCmdPdu(message)));
    }

    private void receiveCmd(UUID client, CmdMessage message) {
        try {
            if (message instanceof CmdEcho) {
                sendCmd(client, message);
            } else if (message instanceof CmdUeCreate) {
                receiveUeCreate(client, (CmdUeCreate) message);
            } else if (message instanceof CmdGnbCreate) {
                ueransim.createGnb(appConfig.createGnbConfig());
                sendCmd(client, new CmdTerminate(0, "gNB created."));
            } else if (message instanceof CmdUeList) {
                receiveUeList(client, (CmdUeList) message);
            } else if (message instanceof CmdUeStatus) {
                receiveUeStatus(client, (CmdUeStatus) message);
            }
        } catch (Exception e) {
            sendCmd(client, new CmdErrorIndication(e.getMessage()));
        }
    }

    private void receiveUeCreate(UUID client, CmdUeCreate cmd) {
        UeConfig refConfig;

        if (cmd.configFile != null) {
            var mts = new MtsContext();
            MtsInitializer.initDefaultMts(mts);

            refConfig = mts.constructor.construct(UeConfig.class,
                    ((ImplicitTypedObject) mts.decoder.decode(cmd.configFile)), true);
        } else {
            refConfig = appConfig.createUeConfig();
        }

        var config = new UeConfig(
                cmd.key != null ? new OctetString(cmd.key) : refConfig.key,
                cmd.op != null ? new OctetString(cmd.op) : refConfig.op,
                refConfig.amf,
                refConfig.imei,
                cmd.imsi != null ? new Supi("imsi", cmd.imsi) : refConfig.supi,
                refConfig.plmn,
                refConfig.smsOverNasSupported,
                refConfig.requestedNssai,
                refConfig.dnn
        );

        ueransim.createUe(config);
        sendCmd(client, new CmdTerminate(0, "UE created: %s.", config.supi));
    }

    private void receiveUeList(UUID client, CmdUeList cmd) {
        var ueNameList = new ArrayList<String>();

        for (var ueId : ueransim.allUes()) {
            var ctx = ueransim.findUe(ueId);
            if (ctx == null)
                continue;
            ueNameList.add(ctx.nodeName);
        }

        var sb = new StringBuilder();
        sb.append("List of UE devices:\n");

        for (var name : ueNameList) {
            sb.append("    ");
            sb.append("- ");
            sb.append(name);
            sb.append("\n");
        }

        if (ueNameList.isEmpty()) {
            sb.append("    - No UEs are available.\n");
        }

        sb.append("\nTotal number of UE: ");
        sb.append(ueNameList.size());

        sendCmd(client, new CmdTerminate(0, sb.toString().trim()));
    }

    private void receiveUeStatus(UUID client, CmdUeStatus message) {
        var nodeName = "ue-" + message.imsi;

        var ctxId = ueransim.findContextIdByNodeName(nodeName);
        if (ctxId == null) {
            sendCmd(client, new CmdErrorIndication("No UE found with the IMSI %s", message.imsi));
            return;
        }

        var ctx = ueransim.findUe(ctxId);
        if (ctx == null) {
            sendCmd(client, new CmdErrorIndication("No UE found with the IMSI %s", message.imsi));
            return;
        }

        Consumer<UeStatusInfo> consumerFunc = ueStatusInfo
                -> sendCmd(client, new CmdTerminate(0, Utils.convertJsonToYaml(Json.toJson(ueStatusInfo))));

        var appTask = ctx.nts.findTask(ItmsId.UE_TASK_APP, UeAppTask.class);
        appTask.push(new IwUeStatusInfoRequest(this, consumerFunc));
    }
}
