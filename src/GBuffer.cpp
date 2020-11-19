/// ============================================================================
/// File    : GBuffer.cpp
/// Version : 0.2
/// Date    : October 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#include "GBuffer.hpp"

#include <cstdlib> // malloc, free
#include <cstring> // memcpy, memset

static inline void *g_aligned_alloc(size_t alignment, size_t size) {
    // Alignment must be a power of two.
    if (alignment & (alignment - 1) || !size) return nullptr;

    // We need extra bytes to store the original value returned by malloc.
    if (alignment < sizeof(void *)) alignment = sizeof(void *);
    void *const malloc_ptr{std::malloc(size + alignment)};
    if (!malloc_ptr) return nullptr;

    // Align to the requested value, leaving room for the original malloc value.
    void *const aligned_ptr{(void *)(((uintptr_t)malloc_ptr + alignment) & -alignment)};

    // Store the original malloc value where it can be found by operator delete.
    ((void **)aligned_ptr)[-1] = malloc_ptr;
    return aligned_ptr;
}

static inline void g_free(void *aligned_ptr) {
    std::free(((void **)aligned_ptr)[-1]);
}

GBuffer::GBuffer(size_t bytes) {
    m_size = bytes;
    m_data = static_cast<char *>(g_aligned_alloc(64, m_size));
    std::memset(m_data, 0, m_size);
    Clear();
}

GBuffer::~GBuffer() {
    g_free(m_data);
}

void GBuffer::Clear() {
    m_next = m_data;
    m_rest = m_size;
}

bool GBuffer::ReadNext(void *dst_buffer, size_t dst_bytes, bool *is_empty) {
    if (dst_bytes <= m_rest) {
        std::memcpy(dst_buffer, m_next, dst_bytes);
        m_next += dst_bytes;
        m_rest -= dst_bytes;

        *is_empty = (m_rest == 0);
        return true;
    }
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
    return false;
}
