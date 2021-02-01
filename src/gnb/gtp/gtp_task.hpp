//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include <memory>
#include <thread>
#include <udp/server_task.hpp>
#include <unordered_map>
#include <utils/logger.hpp>
#include <utils/nts.hpp>
#include <vector>

#include "gnb/gnb_nts.hpp"
#include "gtp_utils.hpp"

namespace nr::gnb
{

struct GnbMrTask;

class GtpTask : public NtsTask
{
  private:
    TaskBase *base;
    std::unique_ptr<Logger> logger;

    udp::UdpServerTask *udpServer;
    std::unordered_map<int, std::unique_ptr<GtpUeContext>> ueContexts;
    std::unique_ptr<IRateLimiter> rateLimiter;
    std::unordered_map<uint64_t, std::unique_ptr<PduSessionResource>> pduSessions;
    PduSessionTree sessionTree;

  public:
    explicit GtpTask(TaskBase *base);
    ~GtpTask() override = default;

  protected:
    void onStart() override;
    void onLoop() override;
    void onQuit() override;

  private:
    void handleUdpReceive(udp::NwUdpServerReceive *msg);
    void handleUeContextUpdate(NwUeContextUpdate *msg);
    void handleSessionCreate(NwPduSessionResourceCreate *msg);
    void handleUplinkData(NwUplinkData *msg);

    void updateAmbrForUe(int ueId);
    void updateAmbrForSession(uint64_t pduSession);
};

} // namespace nr::gnb
