//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include <crypt/crypt_milenage.hpp>
#include <nas/nas.hpp>
#include <nas/nas_timer.hpp>
#include <ue/mm/mm.hpp>
#include <ue/sm/sm.hpp>
#include <ue/ue_nts.hpp>
#include <ue/ue_types.hpp>
#include <utils/nts.hpp>

namespace nr::ue
{

class NasTask : public NtsTask
{
  private:
    TaskBase *base;
    std::unique_ptr<Logger> logger;

    UeTimers timers;
    NasMm *mm;
    NasSm *sm;

  public:
    explicit NasTask(TaskBase *base);
    ~NasTask() override = default;

  protected:
    void onStart() override;
    void onLoop() override;
    void onQuit() override;

  private:
    void onTimerExpire(nas::NasTimer &timer);
    void performTick();
};

} // namespace nr::ue