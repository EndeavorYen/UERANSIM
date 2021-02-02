//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "rls.hpp"
#include <ue/nts.hpp>
#include <urs/rls/ue_entity.hpp>

namespace nr::ue
{

UeRls::UeRls(const std::string &nodeName, const std::vector<InetAddress> &gnbSearchList, std::unique_ptr<Logger> logger,
             NtsTask *targetTask)
    : RlsUeEntity(nodeName, gnbSearchList), m_logger(std::move(logger)), m_targetTask(targetTask)
{
}

void UeRls::logWarn(const std::string &msg)
{
    m_logger->warn(msg);
}

void UeRls::logError(const std::string &msg)
{
    m_logger->err(msg);
}

void UeRls::startWaitingTimer(int period)
{
    m_targetTask->push(new NwRlsStartWaitingTimer(period));
}

void UeRls::searchFailure(rls::ECause cause)
{
    m_targetTask->push(new NwRlsSearchFailure(cause));
}

void UeRls::onRelease(rls::ECause cause)
{
    m_targetTask->push(new NwRlsReleased(cause));
}

void UeRls::onConnect(const std::string &gnbName)
{
    m_targetTask->push(new NwRlsConnected(gnbName));
}

void UeRls::sendRlsPdu(const InetAddress &address, OctetString &&pdu)
{
    m_targetTask->push(new NwRlsSendPdu(address, std::move(pdu)));
}

void UeRls::deliverPayload(rls::EPayloadType type, OctetString &&payload)
{
    m_targetTask->push(new NwDownlinkPayload(type, std::move(payload)));
}

} // namespace nr::ue
