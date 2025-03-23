////////////////////////////////////////////////////////////////////////////////
/// \file      GUdpClient.hpp
/// \version   0.1
/// \date      January 2021
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GUDPCLIENT_HPP
#define GUDPCLIENT_HPP

#include <cstdint> // uint16_t
#include <string>  // string

#include "GBuffer.hpp"

class GUdpClient {
   public:
    GUdpClient(const std::string& remote_addr, uint16_t remote_port);
    ~GUdpClient();

    auto is_ready() { return m_is_ready; }

    bool Receive();

    bool Receive(GBuffer *dst_buffer);

    bool Receive(void *dst_buffer, size_t *dst_bytes) __attribute__((hot));

    bool Send();

    bool Send(GBuffer *src_buffer);

    bool Send(void *src_buffer, size_t src_bytes) __attribute__((hot));

    auto buffer() { return m_buffer; }

   private:
    int      m_socket_fd{-1};
    GBuffer *m_buffer{nullptr};
    bool     m_is_ready{false};
};

#endif // GUDPCLIENT_HPP
