////////////////////////////////////////////////////////////////////////////////
/// \file      GUdpServer.hpp
/// \version   0.1
/// \date      January 2021
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GUDPSERVER_HPP
#define GUDPSERVER_HPP

#include "GBuffer.hpp"

#include <string>
#include <sys/socket.h>

class GUdpServer {
    public:
    GUdpServer(const std::string &local_addr, uint16_t local_port);
    ~GUdpServer();

    auto is_ready() {
        return m_is_ready;
    }

    bool Receive();

    bool Receive(GBuffer *dst_buffer);

    bool Receive(void *dst_buffer, size_t *dst_bytes) __attribute__((hot));

    bool Send();

    bool Send(GBuffer *src_buffer);

    bool Send(void *scr_buffer, size_t src_bytes) __attribute__((hot));

    auto buffer() {
        return m_buffer;
    }

    private:
    int                     m_socket_fd{-1};
    GBuffer *               m_buffer{nullptr};
    bool                    m_is_ready{false};
    struct sockaddr_storage m_peer_addr {};
    socklen_t               m_peer_addr_len{sizeof(struct sockaddr_storage)};
};

#endif // GUDPSERVER_HPP