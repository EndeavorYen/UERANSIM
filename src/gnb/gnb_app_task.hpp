//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include "gnb_types.hpp"
#include <utils/logger.hpp>
#include <memory>
#include <utils/nts.hpp>
#include <thread>
#include <unordered_map>
#include <vector>

namespace nr::gnb
{

class GnbAppTask : public NtsTask
{
  private:
    TaskBase *base;
    std::unique_ptr<Logger> logger;

    GnbStatusInfo statusInfo;

  public:
    explicit GnbAppTask(TaskBase *base);
    ~GnbAppTask() override = default;

  protected:
    void onStart() override;
    void onLoop() override;
    void onQuit() override;
};

} // namespace nr::gnb
