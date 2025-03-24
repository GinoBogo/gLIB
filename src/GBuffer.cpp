////////////////////////////////////////////////////////////////////////////////
/// \file      GBuffer.cpp
/// \version   0.2
/// \date      October 2020
/// \author    Gino Francesco Bogo (ᛊᛟᚱᚱᛖ ᛗᛖᚨ ᛁᛊᛏᚨᛗᛁ ᚨcᚢᚱᛉᚢ)
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GBuffer.hpp"

#include <fmt/core.h> // format

#include <cstdlib> // free, malloc, size_t
#include <cstring> // memcpy, memset

#include "GLogger.hpp" // LOG_WRITE, error

GBuffer::GBuffer(size_t bytes) {
    m_size = bytes;
    m_data = static_cast<char *>(std::malloc(m_size));
    Zeros();
}

GBuffer::~GBuffer() {
    std::free(m_data);
}

void GBuffer::Clear() {
    m_next = m_data;
    m_rest = m_size;
    m_used = 0;
}

void GBuffer::Zeros() {
    m_next = m_data;
    m_rest = m_size;
    m_used = 0;
    std::memset(m_data, 0, m_size);
}

bool GBuffer::Read(void *dst_buffer, size_t dst_bytes) {
    if (dst_bytes <= m_size || dst_buffer == nullptr) {
        std::memcpy(dst_buffer, m_data, dst_bytes);
        m_next = m_data + dst_bytes;
        m_rest = m_size - dst_bytes;
        m_used = dst_bytes;
        return true;
    }
    LOG_WRITE(error, fmt::format("\"{}(...)\" has wrong arguments", __func__));
    return false;
}

bool GBuffer::ReadNext(void *dst_buffer, size_t dst_bytes, bool *is_empty) {
    if (dst_bytes <= m_rest || dst_buffer == nullptr || is_empty == nullptr) {
        std::memcpy(dst_buffer, m_next, dst_bytes);
        m_next += dst_bytes;
        m_rest -= dst_bytes;
        m_used += dst_bytes;

        *is_empty = (m_rest == 0);
        return true;
    }
    LOG_WRITE(error, fmt::format("\"{}(...)\" has wrong arguments", __func__));
    return false;
}

bool GBuffer::Write(const void *src_buffer, size_t src_bytes) {
    if (src_bytes <= m_size || src_buffer == nullptr) {
        std::memcpy(m_data, src_buffer, src_bytes);
        m_next = m_data + src_bytes;
        m_rest = m_size - src_bytes;
        m_used = src_bytes;
        return true;
    }
    LOG_WRITE(error, fmt::format("\"{}(...)\" has wrong arguments", __func__));
    return false;
}

bool GBuffer::WriteNext(const void *src_buffer, size_t src_bytes, bool *is_full) {
    if (src_bytes <= m_rest || src_buffer == nullptr || is_full == nullptr) {
        std::memcpy(m_next, src_buffer, src_bytes);
        m_next += src_bytes;
        m_rest -= src_bytes;
        m_used += src_bytes;

        *is_full = (m_rest == 0);
        return true;
    }
    LOG_WRITE(error, fmt::format("\"{}(...)\" has wrong arguments", __func__));
    return false;
}

bool GBuffer::SetUsed(size_t bytes) {
    if (bytes > m_size) {
        LOG_WRITE(error, fmt::format("\"{}(...)\" has wrong arguments", __func__));
        return false;
    }
    m_next = m_data + bytes;
    m_rest = m_size - bytes;
    m_used = bytes;
    return true;
}

bool GBuffer::ShiftNext(long bytes) {
    auto used{static_cast<long>(m_used) + bytes};
    if (used < 0 || used > static_cast<long>(m_size)) {
        LOG_WRITE(error, fmt::format("\"{}(...)\" has wrong arguments", __func__));
        return false;
    }
    if (bytes >= 0) {
        m_next += static_cast<size_t>(bytes);
        m_rest -= static_cast<size_t>(bytes);
        m_used += static_cast<size_t>(bytes);
    } else {
        m_next -= static_cast<size_t>(-bytes);
        m_rest += static_cast<size_t>(-bytes);
        m_used -= static_cast<size_t>(-bytes);
    }
    return true;
}
