/// ============================================================================
/// File    : GFilePipe.hpp
/// Version : 0.2
/// Date    : December 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GFILEPIPE_HPP
#define GFILEPIPE_HPP

#include "GPingPong.hpp"

class GFilePipe {
    public:
    GFilePipe(const std::string &filename, size_t chunk_bytes, size_t chunks_number, GPingPong::StreamType stream_type);

    ~GFilePipe();

    inline void Read(void *dst_buffer, size_t dst_bytes) {
        m_ping_pong->Read(dst_buffer, dst_bytes);
    }

    inline void Write(void *src_buffer, size_t src_bytes) {
        m_ping_pong->Write(src_buffer, src_bytes);
    }

    private:
    std::any   m_user_data;
    GPingPong *m_ping_pong;
};

#endif // GFILEPIPE_HPP