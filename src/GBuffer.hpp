/// ============================================================================
/// File    : GBuffer.hpp
/// Version : 0.2
/// Date    : October 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GBUFFER_HPP
#define GBUFFER_HPP

#include <cstddef> // size_t

class GBuffer {
    public:
    GBuffer(size_t bytes);

    ~GBuffer();

    void Clear();

    void Zeros();

    bool Read(void *dst_buffer, size_t dst_bytes);

    bool ReadNext(void *dst_buffer, size_t dst_bytes, bool *is_empty);

    bool Write(const void *src_buffer, size_t src_bytes);

    bool WriteNext(const void *src_buffer, size_t src_bytes, bool *is_full);

    bool SetUsed(size_t bytes);

    bool ShiftNext(long bytes);

    inline auto *data() {
        return m_data;
    }

    inline auto size() {
        return m_size;
    }

    inline auto rest() {
        return m_rest;
    }

    inline auto used() {
        return m_used;
    }

    private:
    char * m_data;
    char * m_next;
    size_t m_size;
    size_t m_rest;
    size_t m_used;
};

#endif // GBUFFER_HPP
