/// ============================================================================
/// File    : GBuffer.cpp
/// Version : 0.2
/// Date    : October 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#include "GBuffer.hpp"

#include <cstdlib>
#include <cstring>

#ifdef _LIBCPP_HAS_ALIGNED_ALLOC || _GLIBCXX_HAVE_ALIGNED_ALLOC
#define ALIGNED_ALLOC(alignment, size) std::aligned_alloc(alignment, size)
#define ALIGNED_FREE(pointer)          std::free(pointer)
#else
#define ALIGNED_ALLOC(alignment, size) ::_aligned_malloc(size, alignment)
#define ALIGNED_FREE(pointer)          ::_aligned_free(pointer)
#endif

GBuffer::GBuffer(size_t bytes) {
    m_size = bytes;
    m_data = static_cast<char *>(ALIGNED_ALLOC(64, m_size));
    memset(m_data, 0, m_size);
    Clear();
}

GBuffer::~GBuffer() {
    ALIGNED_FREE(m_data);
}

void GBuffer::Clear() {
    m_next = m_data;
    m_rest = m_size;
}

bool GBuffer::ReadNext(void *dst_buffer, size_t dst_bytes, bool *is_empty) {
    if (dst_bytes <= m_rest) {
        memcpy(dst_buffer, m_next, dst_bytes);
        m_next += dst_bytes;
        m_rest -= dst_bytes;

        *is_empty = (m_rest == 0);
        return true;
    }
    return false;
}

bool GBuffer::WriteNext(const void *src_buffer, size_t src_bytes, bool *is_full) {
    if (src_bytes <= m_rest) {
        memcpy(m_next, src_buffer, src_bytes);
        m_next += src_bytes;
        m_rest -= src_bytes;

        *is_full = (m_rest == 0);
        return true;
    }
    return false;
}