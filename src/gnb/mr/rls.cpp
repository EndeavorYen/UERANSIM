//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "rls.hpp"
#include <gnb/nts.hpp>

namespace nr::gnb
{

GnbRls::GnbRls(std::string nodeName, std::unique_ptr<Logger> logger, NtsTask *targetTask)
    : RlsGnbEntity(std::move(nodeName)), m_logger(std::move(logger)), m_targetTask(targetTask), m_isN1Ready{}
{
}

void GnbRls::logWarn(const std::string &msg)
{
    m_logger->warn(msg);
}

void GnbRls::logError(const std::string &msg)
{
    m_logger->err(msg);
}

bool GnbRls::isInReadyState()
{
    return m_isN1Ready;
}

void GnbRls::onUeConnected(int ue, std::string name)
{
    m_targetTask->push(new NwUeConnected(ue, std::move(name)));
}

void GnbRls::onUeReleased(int ue, rls::ECause cause)
{
    m_targetTask->push(new NwUeReleased(ue, cause));
}

void GnbRls::deliverUplinkPayload(int ue, rls::EPayloadType type, OctetString &&payload)
{
    m_targetTask->push(new NwUplinkPayload(ue, type, std::move(payload)));
}

void GnbRls::sendRlsPdu(const InetAddress &address, OctetString &&pdu)
{
    m_targetTask->push(new NwRlsSendPdu(address, std::move(pdu)));
}

void GnbRls::setN1IsReady(bool isReady)
{
    m_isN1Ready = isReady;
}

} // namespace nr::gnb
