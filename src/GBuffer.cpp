/// ============================================================================
/// File    : GBuffer.cpp
/// Version : 0.2
/// Date    : October 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#include "GBuffer.hpp"

#include "GLogger.hpp"

#include <cstdlib>    // malloc, free
#include <cstring>    // memcpy, memset
#include <fmt/core.h> // format

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
}

void GBuffer::Zeros() {
    m_next = m_data;
    m_rest = m_size;
    std::memset(m_data, 0, m_size);
}

bool GBuffer::ReadNext(void *dst_buffer, size_t dst_bytes, bool *is_empty) {
    if (dst_bytes <= m_rest) {
        std::memcpy(dst_buffer, m_next, dst_bytes);
        m_next += dst_bytes;
        m_rest -= dst_bytes;

        *is_empty = (m_rest == 0);
        return true;
    }
    LOG_WRITE(error, fmt::format("Not enough bytes to execute \"{}\"", __func__));
    return false;
}

bool GBuffer::WriteNext(const void *src_buffer, size_t src_bytes, bool *is_full) {
    if (src_bytes <= m_rest) {
        std::memcpy(m_next, src_buffer, src_bytes);
        m_next += src_bytes;
        m_rest -= src_bytes;

        *is_full = (m_rest == 0);
        return true;
    }
    LOG_WRITE(error, fmt::format("Not enough bytes to execute \"{}\"", __func__));
    return false;
}
