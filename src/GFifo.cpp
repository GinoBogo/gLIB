////////////////////////////////////////////////////////////////////////////////
/// \file      GFifo.cpp
/// \version   0.1
/// \date      April 2021
/// \author    Gino Francesco Bogo (ᛊᛟᚱᚱᛖ ᛗᛖᚨ ᛁᛊᛏᚨᛗᛁ ᚨcᚢᚱᛉᚢ)
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GFifo.hpp"

#include <cstdlib> // free, malloc, size_t
#include <cstring> // memcpy, memset

typedef union {
    size_t *size;
    char   *ptr;
} size_ptr;

GFifo::GFifo(size_t bytes, size_t depth) : m_bytes(bytes + sizeof(size_t)), m_depth(depth) {
    m_data = static_cast<char *>(std::malloc(m_bytes * m_depth));
    zeros();
}

GFifo::~GFifo() {
    std::free(m_data);
}

void GFifo::reset_metrics() {
    m_overflow  = 0;
    m_underflow = 0;
}

void GFifo::clear() {
    m_iR   = 0;
    m_iW   = 0;
    m_free = m_depth;
    m_used = 0;
    reset_metrics();
}

void GFifo::zeros() {
    clear();
    std::memset(m_data, 0, m_bytes * m_depth);
}

void GFifo::ResetMetrics() {
    const std::lock_guard<std::mutex> lock(m_mutex);
    reset_metrics();
}

void GFifo::Clear() {
    const std::lock_guard<std::mutex> lock(m_mutex);
    clear();
}

void GFifo::Zeros() {
    const std::lock_guard<std::mutex> lock(m_mutex);
    zeros();
}

bool GFifo::Push(void *src_buffer, size_t src_bytes) {
    auto result{false};
    if (src_buffer != nullptr && src_bytes <= (m_bytes - sizeof(size_t))) {
        size_ptr __dst;
        {
            const std::lock_guard<std::mutex> lock(m_mutex);
            if (m_free > 0) {
                --m_free;
                ++m_used;

                __dst.ptr = m_data + (m_iW * m_bytes);

                if (++m_iW == m_depth) {
                    m_iW = 0;
                }

                *__dst.size = src_bytes;
                memcpy(__dst.ptr + sizeof(size_t), src_buffer, src_bytes);
                result = true;
            } else {
                ++m_overflow;
            }
        }
    }
    return result;
}

bool GFifo::Pop(void *dst_buffer, size_t *dst_bytes) {
    auto result{false};
    if (dst_buffer != nullptr && dst_bytes != nullptr) {
        size_ptr __src;
        {
            const std::lock_guard<std::mutex> lock(m_mutex);
            if (m_used > 0) {
                ++m_free;
                --m_used;

                __src.ptr = m_data + (m_iR * m_bytes);

                if (++m_iR == m_depth) {
                    m_iR = 0;
                }

                *dst_bytes = *__src.size;
                memcpy(dst_buffer, __src.ptr + sizeof(size_t), *dst_bytes);
                result = true;
            } else {
                ++m_underflow;
            }
        }
    }
    return result;
}
