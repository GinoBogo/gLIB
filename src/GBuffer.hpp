/// ============================================================================
/// File    : GBuffer.hpp
/// Version : 0.2
/// Date    : October 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GBUFFER_HPP
#define GBUFFER_HPP

#ifdef __APPLE__
#ifndef __FreeBSD__
#define __FreeBSD__
#endif
#endif

#include <cstddef> // size_t

class GBuffer {
    public:
    GBuffer(size_t bytes);

    ~GBuffer();

    void Clear();

    bool ReadNext(void *dst_buffer, size_t dst_bytes, bool *is_empty);

    bool WriteNext(const void *src_buffer, size_t src_bytes, bool *is_full);

    auto *data() {
        return m_data;
    }

    auto size() {
        return m_size;
    }

    auto rest() {
        return m_rest;
    }

    private:
    char * m_data;
    char * m_next;
    size_t m_size;
    size_t m_rest;
};

#endif // GBUFFER_HPP
