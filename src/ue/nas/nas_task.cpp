//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "nas_task.hpp"
#include "ue_nts.hpp"

static const int NTS_TIMER_ID_NAS_TIMER_CYCLE = 1;
static const int NTS_TIMER_ID_MM_CYCLE = 2;
static const int NTS_TIMER_INTERVAL_NAS_TIMER_CYCLE = 1000;
static const int NTS_TIMER_INTERVAL_MM_CYCLE = 400;

namespace nr::ue
{

NasTask::NasTask(TaskBase *base) : base{base}, timers{}
{
    logger = base->logBase->makeUniqueLogger(base->config->getLoggerPrefix() + "nas");

    mm = new NasMm(base, this, &timers);
    sm = new NasSm(base, this, &timers);
}

void NasTask::onStart()
{
    logger->debug("NAS layer started");

    sm->onStart(mm);
    mm->onStart(sm);

    setTimer(NTS_TIMER_ID_NAS_TIMER_CYCLE, NTS_TIMER_INTERVAL_NAS_TIMER_CYCLE);
    setTimer(NTS_TIMER_ID_MM_CYCLE, NTS_TIMER_INTERVAL_MM_CYCLE);

    mm->triggerMmCycle();
}

void NasTask::onQuit()
{
    mm->onQuit();
    sm->onQuit();

    delete mm;
    delete sm;
}

void NasTask::onLoop()
{
    NtsMessage *msg = take();
    if (!msg)
        return;

    switch (msg->msgType)
    {
    case NtsMessageType::UE_DOWNLINK_NAS_DELIVERY: {
        auto *w = dynamic_cast<NwDownlinkNasDelivery *>(msg);
        OctetString nasPdu = std::move(w->nasPdu);
        delete w;
        OctetBuffer buffer{nasPdu};
        std::unique_ptr<nas::NasMessage> nasMessage = nas::DecodeNasMessage(buffer);
        if (nasMessage != nullptr)
            mm->receiveNasMessage(*nasMessage);
        break;
    }
    case NtsMessageType::NAS_TIMER_EXPIRE: {
        auto *w = dynamic_cast<NwNasTimerExpire *>(msg);
        nas::NasTimer *timer = w->timer;
        delete w;
        onTimerExpire(*timer);
        break;
    }
    case NtsMessageType::UE_EXTERNAL_COMMAND: {
        // TODO
        delete msg;
        break;
    }
    case NtsMessageType::UE_MR_PLMN_SEARCH_RESPONSE: {
        auto *w = dynamic_cast<NwPlmnSearchResponse *>(msg);
        mm->receivePlmnSearchResponse(*w);
        delete w;
        break;
    }
    case NtsMessageType::TIMER_EXPIRED: {
        auto *w = dynamic_cast<NwTimerExpired *>(msg);
        int timerId = w->timerId;
        delete w;
        if (timerId == NTS_TIMER_ID_NAS_TIMER_CYCLE)
        {
            setTimer(NTS_TIMER_ID_NAS_TIMER_CYCLE, NTS_TIMER_INTERVAL_NAS_TIMER_CYCLE);
            performTick();
        }
        if (timerId == NTS_TIMER_ID_MM_CYCLE)
        {
            setTimer(NTS_TIMER_ID_MM_CYCLE, NTS_TIMER_INTERVAL_MM_CYCLE);
            mm->performMmCycle();
        }
        break;
    }
    case NtsMessageType::NAS_PERFORM_MM_CYCLE: {
        delete msg;
        mm->performMmCycle();
        break;
    }
    case NtsMessageType::UE_TRIGGER_INITIAL_SESSION_CREATE: {
        sm->establishInitialSessions();
        delete msg;
        break;
    }
    default:
        logger->err("Unhandled NTS message received with type %d", (int)msg->msgType);
        delete msg;
        break;
    }
}

void NasTask::onTimerExpire(nas::NasTimer &timer)
{
    if (timer.isMmTimer())
        mm->onTimerExpire(timer);
    else
    {
        // TODO
    }
}

void NasTask::performTick()
{
    auto sendExpireMsg = [this](nas::NasTimer *timer) { push(new NwNasTimerExpire(timer)); };

    if (timers.t3346.performTick())
        sendExpireMsg(&timers.t3346);
    if (timers.t3396.performTick())
        sendExpireMsg(&timers.t3396);
    if (timers.t3444.performTick())
        sendExpireMsg(&timers.t3444);
    if (timers.t3445.performTick())
        sendExpireMsg(&timers.t3445);
    if (timers.t3502.performTick())
        sendExpireMsg(&timers.t3502);
    if (timers.t3510.performTick())
        sendExpireMsg(&timers.t3510);
    if (timers.t3511.performTick())
        sendExpireMsg(&timers.t3511);
    if (timers.t3512.performTick())
        sendExpireMsg(&timers.t3512);
    if (timers.t3516.performTick())
        sendExpireMsg(&timers.t3516);
    if (timers.t3517.performTick())
        sendExpireMsg(&timers.t3517);
    if (timers.t3519.performTick())
        sendExpireMsg(&timers.t3519);
    if (timers.t3520.performTick())
        sendExpireMsg(&timers.t3520);
    if (timers.t3521.performTick())
        sendExpireMsg(&timers.t3521);
    if (timers.t3525.performTick())
        sendExpireMsg(&timers.t3525);
    if (timers.t3540.performTick())
        sendExpireMsg(&timers.t3540);
    if (timers.t3580.performTick())
        sendExpireMsg(&timers.t3580);
    if (timers.t3581.performTick())
        sendExpireMsg(&timers.t3581);
    if (timers.t3582.performTick())
        sendExpireMsg(&timers.t3582);
    if (timers.t3583.performTick())
        sendExpireMsg(&timers.t3583);
    if (timers.t3584.performTick())
        sendExpireMsg(&timers.t3584);
    if (timers.t3585.performTick())
        sendExpireMsg(&timers.t3585);
}

} // namespace nr::ue