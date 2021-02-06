//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include <cstdint>
#include <memory>

template <typename Deleter = std::default_delete<const uint8_t[]>>
class UniqueBuffer
{
    const uint8_t *m_data;
    size_t m_length;

  public:
    inline UniqueBuffer(const uint8_t *data, size_t length) noexcept : m_data(data), m_length(length)
    {
    }

    inline ~UniqueBuffer() noexcept
    {
        Deleter{}(m_data);
    }

    UniqueBuffer(const UniqueBuffer &m) = delete;

    inline UniqueBuffer(UniqueBuffer &&m) noexcept : m_data(m.m_data), m_length(m.m_length)
    {
        m.m_data = nullptr;
        m.m_length = 0;
    }

    UniqueBuffer &operator=(const UniqueBuffer &m) = delete;

    inline UniqueBuffer &operator=(UniqueBuffer &&m) noexcept
    {
        m_data = m.m_data;
        m_length = m.m_length;
        return *this;
    }

    [[nodiscard]] inline const uint8_t *data() const
    {
        return m_data;
    }

    [[nodiscard]] inline size_t length() const
    {
        return m_length;
    }
};
