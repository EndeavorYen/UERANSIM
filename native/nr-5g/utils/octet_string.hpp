//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include "octet.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

class OctetString
{
  private:
    std::vector<uint8_t> m_data;

  public:
    OctetString() : m_data()
    {
    }

    explicit OctetString(std::vector<uint8_t> &&data) : m_data(std::move(data))
    {
    }

    OctetString(OctetString &&octetString) noexcept : m_data(std::move(octetString.m_data))
    {
    }

  public:
    void append(const OctetString &v);
    void appendOctet(uint8_t v);
    void appendOctet(int v);
    void appendOctet(int bigHalf, int littleHalf);
    void appendOctet2(octet2 v);
    void appendOctet2(int v);
    void appendOctet3(octet3 v);
    void appendOctet3(int v);
    void appendOctet4(octet4 v);
    void appendOctet4(int v);

    const uint8_t* data() const;
    const uint8_t* data();
    int length() const;
};
