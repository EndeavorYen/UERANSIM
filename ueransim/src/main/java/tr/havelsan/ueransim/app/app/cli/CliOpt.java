/*
 * This file is a part of UERANSIM open source project.
 * Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
 *
 * The software and all associated files are licensed under GPL-3.0
 * and subject to the terms and conditions defined in LICENSE file.
 */

package tr.havelsan.ueransim.app.app.cli;

import picocli.CommandLine;
import tr.havelsan.ueransim.app.common.GnbId;
import tr.havelsan.ueransim.app.common.Supi;
import tr.havelsan.ueransim.app.common.cli.*;

import java.io.File;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

public class CliOpt {

    public static CmdMessage msg;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(name = "nr-cli",
            subcommands = {
                    GnbCreateCommand.class,
                    UeCreateCommand.class,
                    GnbListCommand.class,
                    UeListCommand.class,
                    GnbStatusCommand.class,
                    UeStatusCommand.class,
                    SessionCreateCommand.class,
                    UePingCommand.class,
                    UeDeRegistrationCommand.class,
            },
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    public static class RootCommand {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "ue-create",
            description = "Create and initialize a new UE",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = false)
    public static class UeCreateCommand implements Runnable {
        @CommandLine.Option(
                names = {"-c", "--config"},
                description = "Use the specified config file for the new UE. If no files are provided, default " +
                        "UE configuration of selected profile is used."
        )
        private File configFile;

        @CommandLine.Option(
                names = {"-i", "--imsi"},
                description = "Use specified SUPI/IMSI number instead of default one."
        )
        private String imsi;

        @CommandLine.Option(
                names = {"-k", "--key"},
                description = "Use specified KEY instead of default one."
        )
        private String key;

        @CommandLine.Option(
                names = {"-p", "--op"},
                description = "Use specified OP instead of default one."
        )
        private String op;

        public void run() {
            var msg = new CmdUeCreate();
            msg.configFile = configFile != null ? configFile.getAbsolutePath() : null;
            msg.imsi = imsi;
            msg.key = key;
            msg.op = op;

            CliOpt.msg = msg;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "ue-list",
            description = "List all the UEs associated with this UERANSIM agent",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = true)
    public static class UeListCommand implements Runnable {
        public void run() {
            msg = new CmdUeList();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "ue-status",
            description = "Dump some information about specified UE's general status",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = true)
    public static class UeStatusCommand implements Runnable {
        @CommandLine.Parameters(
                description = "IMSI number of the UE whose status will be displayed."
        )
        private Supi imsi;

        public void run() {
            msg = new CmdUeStatus(imsi != null ? imsi.value : null);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "gnb-create",
            description = "Create and initialize a new GNB",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = false)
    public static class GnbCreateCommand implements Runnable {
        @CommandLine.Option(
                names = {"-c", "--config"},
                description = "Use the specified config file for the new gNB. If no files are provided, default " +
                        "gNB configuration of selected profile is used."
        )
        private File configFile;

        @CommandLine.Option(
                names = {"-i", "--id"},
                description = "Use specified ID instead of default one."
        )
        private int id;

        public void run() {
            var msg = new CmdGnbCreate();
            msg.configFile = configFile != null ? configFile.getAbsolutePath() : null;
            msg.id = id;

            CliOpt.msg = msg;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "gnb-list",
            description = "List all the gNBs associated with this UERANSIM agent",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = true)
    public static class GnbListCommand implements Runnable {
        public void run() {
            msg = new CmdGnbList();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "gnb-status",
            description = "Dump some information about specified gNB's general status",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = true)
    public static class GnbStatusCommand implements Runnable {
        @CommandLine.Parameters(
                description = "ID of the gNB whose status will be displayed."
        )
        private GnbId id;

        public void run() {
            msg = new CmdGnbStatus(id != null ? id.value : 0);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "session-create",
            description = "Trigger a PDU session establishment for a specified UE",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = false)
    public static class SessionCreateCommand implements Runnable {
        @CommandLine.Parameters(
                description = "IMSI of the UE that will trigger PDU session establishment."
        )
        private Supi ueImsi;

        public void run() {
            msg = new CmdSessionCreate(ueImsi != null ? ueImsi.value : null);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "ue-ping",
            description = "Trigger a ping request for the specified UE",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = false)
    public static class UePingCommand implements Runnable {
        @CommandLine.Parameters(
                description = "IMSI number of the UE that will trigger ping request.",
                index = "0"
        )
        private Supi ueImsi;

        @CommandLine.Parameters(
                description = "Destination address of the ping request. (NOTE: address resolution is performed locally.)",
                index = "1"
        )
        private String address;

        @CommandLine.Option(
                names = {"-c", "--count"},
                description = "Send specified number of consequential ping requests. Typically an integer in range [1, 10] is used.",
                defaultValue = "1",
                showDefaultValue = CommandLine.Help.Visibility.ALWAYS
        )
        private int count;

        @CommandLine.Option(
                names = {"-t", "--timeout"},
                description = "Use specified timeout value instead of default one (in seconds).",
                defaultValue = "3",
                showDefaultValue = CommandLine.Help.Visibility.ALWAYS
        )
        private int timeoutSec;

        public void run() {
            var msg = new CmdUePing();
            msg.ueImsi = ueImsi.value;
            msg.address = address;
            msg.count = count;
            msg.timeoutSec = timeoutSec;

            CliOpt.msg = msg;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @CommandLine.Command(
            name = "ue-deregister",
            description = "Trigger a de-registration for the specified UE",
            sortOptions = false,
            mixinStandardHelpOptions = true,
            versionProvider = CliClient.VersionProvider.class
    )
    @CommandInfo(isQuery = false)
    public static class UeDeRegistrationCommand implements Runnable {
        @CommandLine.Parameters(
                description = "IMSI number of the UE that will trigger de-registration.",
                index = "0"
        )
        private Supi ueImsi;

        @CommandLine.Option(
                names = {"-s"},
                description = "Use switch-off indication in de-registration request."
        )
        private boolean isSwitchOff;

        public void run() {
            var msg = new CmdUeDeRegistration();
            msg.ueImsi = ueImsi != null ? ueImsi.value : null;
            msg.isSwitchOff = isSwitchOff;

            CliOpt.msg = msg;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @Retention(RetentionPolicy.RUNTIME)
    public @interface CommandInfo {
        boolean isQuery();
    }
}
