//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include <memory>
#include <sctp/sctp.hpp>
#include <thread>
#include <unordered_map>
#include <utils/logger.hpp>
#include <utils/nts.hpp>
#include <utils/scoped_thread.hpp>
#include <vector>

#include "gnb/nts.hpp"

namespace nr::gnb
{

class SctpTask : public NtsTask
{
  private:
    struct ClientEntry
    {
        int id;
        sctp::SctpClient *client;
        ScopedThread *receiverThread;
        sctp::ISctpHandler *handler;
        NtsTask *associatedTask;
    };

  private:
    TaskBase *base;
    std::unique_ptr<Logger> logger;
    std::unordered_map<int, ClientEntry *> clients;

  public:
    explicit SctpTask(TaskBase *base);
    ~SctpTask() override = default;

  protected:
    void onStart() override;
    void onLoop() override;
    void onQuit() override;

  private:
    static void DeleteClientEntry(ClientEntry *entry);

  private:
    void receiveSctpConnectionSetupRequest(NwSctpConnectionRequest *msg);
    void receiveAssociationSetup(NwSctpAssociationSetup *msg);
    void receiveAssociationShutdown(NwSctpAssociationShutdown *msg);
    void receiveClientReceive(NwSctpClientReceive *msg);
    void receiveUnhandledNotification(NwSctpUnhandledNotificationReceive *msg);
    void receiveConnectionClose(NwSctpConnectionClose *msg);
    void receiveSendMessage(NwSctpSendMessage *msg);
};

} // namespace nr::gnb