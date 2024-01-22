////////////////////////////////////////////////////////////////////////////////
/// \file      GFilePipe.hpp
/// \version   0.2
/// \date      December 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GFILEPIPE_HPP
#define GFILEPIPE_HPP

#include "GPingPong.hpp"

class GFilePipe {
  public:
    GFilePipe(const std::string& filename_fmt, size_t chunk_bytes, size_t chunks_number, GPingPong::StreamType stream_type);

    ~GFilePipe();

    inline bool Read(void* dst_buffer, size_t dst_bytes) {
        return m_ping_pong->Read(dst_buffer, dst_bytes);
    }

    inline bool Write(void* src_buffer, size_t src_bytes) {
        return m_ping_pong->Write(src_buffer, src_bytes);
    }

  private:
    std::any   m_user_data;
    GPingPong* m_ping_pong;
};

#endif // GFILEPIPE_HPP
