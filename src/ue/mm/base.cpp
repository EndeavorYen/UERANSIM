//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "mm.hpp"

#include <nas/utils.hpp>
#include <utils/common.hpp>

namespace nr::ue
{

NasMm::NasMm(TaskBase *base, NtsTask *nas, UeTimers *timers) : m_base{base}, m_nas{nas}, m_timers{timers}, m_sm{nullptr}
{
    m_logger = base->logBase->makeUniqueLogger(base->config->getLoggerPrefix() + "nas");

    m_rmState = ERmState::RM_DEREGISTERED;
    m_cmState = ECmState::CM_IDLE;
    m_mmState = EMmState::MM_DEREGISTERED;
    m_mmSubState = EMmSubState::MM_DEREGISTERED_NA;
    m_emulationMode = base->config->emulationMode;
    m_validSim = base->config->supi.has_value();
}

void NasMm::onStart(NasSm *sm)
{
    m_sm = sm;

    auto *statusUpdate = new NwUeStatusUpdate(NwUeStatusUpdate::MM_STATE);
    statusUpdate->mmState = MmStateName(m_mmState);
    statusUpdate->mmSubState = MmSubStateName(m_mmSubState);
    m_base->appTask->push(statusUpdate);

    statusUpdate = new NwUeStatusUpdate(NwUeStatusUpdate::RM_STATE);
    statusUpdate->rmState = RmStateName(m_rmState);
    m_base->appTask->push(statusUpdate);
}

void NasMm::onQuit()
{
    // TODO
}

void NasMm::triggerMmCycle()
{
    m_nas->push(new NwPerformMmCycle());
}

void NasMm::performMmCycle()
{
    if (m_mmState == EMmState::MM_NULL)
        return;

    if (m_mmSubState == EMmSubState::MM_DEREGISTERED_NA)
    {
        if (m_validSim)
        {
            switchMmState(EMmState::MM_DEREGISTERED, EMmSubState::MM_DEREGISTERED_PLMN_SEARCH);
        }
        else
        {
            switchMmState(EMmState::MM_DEREGISTERED, EMmSubState::MM_DEREGISTERED_NO_SUPI);
        }
    }

    if (m_mmSubState == EMmSubState::MM_DEREGISTERED_PLMN_SEARCH)
    {
        long current = utils::CurrentTimeMillis();
        long elapsedMs = current - m_lastPlmnSearchTrigger;
        if (elapsedMs > 50)
        {
            m_base->rrcTask->push(new NwPlmnSearchRequest());
            m_lastPlmnSearchTrigger = current;
        }
        return;
    }

    if (m_mmSubState == EMmSubState::MM_DEREGISTERED_NORMAL_SERVICE)
    {
        if (m_emulationMode && !m_timers->t3346.isRunning())
            sendRegistration(nas::ERegistrationType::INITIAL_REGISTRATION, nas::EFollowOnRequest::FOR_PENDING);
        return;
    }

    if (m_mmState == EMmState::MM_REGISTERED_INITIATED)
        return;
    if (m_mmSubState == EMmSubState::MM_REGISTERED_NORMAL_SERVICE)
        return;
    if (m_mmState == EMmState::MM_DEREGISTERED_INITIATED)
        return;
    if (m_mmSubState == EMmSubState::MM_DEREGISTERED_NA)
        return;
    if (m_mmSubState == EMmSubState::MM_DEREGISTERED_NO_SUPI)
        return;
    if (m_mmSubState == EMmSubState::MM_DEREGISTERED_NO_CELL_AVAILABLE)
        return;
    if (m_mmSubState == EMmSubState::MM_REGISTERED_NO_CELL_AVAILABLE)
        return;

    if (m_emulationMode)
    {
        m_logger->err("unhandled UE MM state");
        return;
    }
}

void NasMm::switchMmState(EMmState state, EMmSubState subState)
{
    EMmState oldState = m_mmState;
    EMmSubState oldSubState = m_mmSubState;

    m_mmState = state;
    m_mmSubState = subState;

    onSwitchMmState(oldState, m_mmState, oldSubState, m_mmSubState);

    if (m_base->nodeListener)
    {
        m_base->nodeListener->onSwitch(app::NodeType::UE, m_base->config->getNodeName(), app::StateType::MM,
                                       MmSubStateName(oldSubState), MmSubStateName(subState));
        m_base->nodeListener->onSwitch(app::NodeType::UE, m_base->config->getNodeName(), app::StateType::MM_SUB,
                                       MmStateName(oldState), MmStateName(state));
    }

    auto *statusUpdate = new NwUeStatusUpdate(NwUeStatusUpdate::MM_STATE);
    statusUpdate->mmState = MmStateName(state);
    statusUpdate->mmSubState = MmSubStateName(subState);
    m_base->appTask->push(statusUpdate);

    m_logger->info("UE switches to state: %s", MmSubStateName(subState));

    triggerMmCycle();
}

void NasMm::switchRmState(ERmState state)
{
    ERmState oldState = m_rmState;
    m_rmState = state;

    onSwitchRmState(oldState, m_rmState);

    if (m_base->nodeListener)
    {
        m_base->nodeListener->onSwitch(app::NodeType::UE, m_base->config->getNodeName(), app::StateType::RM,
                                       RmStateName(oldState), RmStateName(m_rmState));
    }

    auto *statusUpdate = new NwUeStatusUpdate(NwUeStatusUpdate::RM_STATE);
    statusUpdate->rmState = RmStateName(state);
    m_base->appTask->push(statusUpdate);

    m_logger->info("UE switches to state: %s", RmStateName(state));

    triggerMmCycle();
}

void NasMm::onSwitchMmState(EMmState oldState, EMmState newState, EMmSubState oldSubState, EMmSubState newSubSate)
{
    // The UE shall mark the 5G NAS security context on the USIM or in the non-volatile memory as invalid when the UE
    // initiates an initial registration procedure as described in subclause 5.5.1.2 or when the UE leaves state
    // 5GMM-DEREGISTERED for any other state except 5GMM-NULL.
    if (oldState == EMmState::MM_DEREGISTERED && newState != EMmState::MM_DEREGISTERED && newState != EMmState::MM_NULL)
    {
        if (m_currentNsCtx.has_value() || m_nonCurrentNsCtx.has_value())
        {
            m_logger->debug("Deleting NAS security context");

            m_currentNsCtx = {};
            m_nonCurrentNsCtx = {};
        }
    }
}

void NasMm::onSwitchRmState(ERmState oldState, ERmState newState)
{
}

void NasMm::receivePlmnSearchResponse(const NwPlmnSearchResponse &msg)
{
    if (m_base->nodeListener)
        m_base->nodeListener->onConnected(app::NodeType::UE, m_base->config->getNodeName(), app::NodeType::GNB,
                                          msg.gnbName);

    m_logger->info("UE connected to gNB");

    if (m_mmSubState == EMmSubState::MM_REGISTERED_PLMN_SEARCH)
        switchMmState(EMmState::MM_REGISTERED, EMmSubState::MM_REGISTERED_NORMAL_SERVICE);
    else if (m_mmSubState == EMmSubState::MM_DEREGISTERED_PLMN_SEARCH)
        switchMmState(EMmState::MM_DEREGISTERED, EMmSubState::MM_DEREGISTERED_NORMAL_SERVICE);
}

void NasMm::receivePlmnSearchFailure()
{
    if (m_mmSubState == EMmSubState::MM_REGISTERED_PLMN_SEARCH)
        switchMmState(EMmState::MM_REGISTERED, EMmSubState::MM_REGISTERED_NO_CELL_AVAILABLE);
    else if (m_mmSubState == EMmSubState::MM_DEREGISTERED_PLMN_SEARCH)
        switchMmState(EMmState::MM_DEREGISTERED, EMmSubState::MM_DEREGISTERED_NO_CELL_AVAILABLE);
}

void NasMm::onTimerExpire(nas::NasTimer &timer)
{
    switch (timer.getCode())
    {
    case 3512: {
        if (m_emulationMode && m_mmState == EMmState::MM_REGISTERED)
        {
            sendRegistration(nas::ERegistrationType::PERIODIC_REGISTRATION_UPDATING,
                             nas::EFollowOnRequest::FOR_PENDING);
        }
        break;
    }
    case 3346: {
        if (m_emulationMode && m_mmSubState == EMmSubState::MM_DEREGISTERED_NORMAL_SERVICE)
        {
            sendRegistration(nas::ERegistrationType::INITIAL_REGISTRATION, nas::EFollowOnRequest::FOR_PENDING);
        }
        break;
    }
    }
}

} // namespace nr::ue
