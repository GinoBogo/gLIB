////////////////////////////////////////////////////////////////////////////////
/// \file      GBuffer.hpp
/// \version   0.2
/// \date      October 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GBUFFER_HPP
#define GBUFFER_HPP

#include <cstddef> // size_t

class GBuffer {
    public:
    GBuffer(size_t bytes);

    ~GBuffer();

    void Clear() __attribute__((cold));

    void Zeros() __attribute__((cold));

    bool Read(void *dst_buffer, size_t dst_bytes);

    bool ReadNext(void *dst_buffer, size_t dst_bytes, bool *is_empty) __attribute__((hot));

    bool Write(const void *src_buffer, size_t src_bytes);

    bool WriteNext(const void *src_buffer, size_t src_bytes, bool *is_full) __attribute__((hot));

    bool SetUsed(size_t bytes) __attribute__((hot));

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
