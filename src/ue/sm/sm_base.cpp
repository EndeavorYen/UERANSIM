//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "sm.hpp"

namespace nr::ue
{

NasSm::NasSm(TaskBase *base, NtsTask *nas, UeTimers *timers) : m_base(base), m_nas(nas), m_timers(timers), m_mm(nullptr)
{
    m_logger = base->logBase->makeUniqueLogger(base->config->getLoggerPrefix() + "nas");
}

void NasSm::onStart(NasMm *mm)
{
    m_mm = mm;
}

void NasSm::onQuit()
{
    // TODO
}

} // namespace nr::ue