////////////////////////////////////////////////////////////////////////////////
/// \file      GUdpServer.cpp
/// \version   0.1
/// \date      January 2021
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GUdpServer.hpp"

#include "GLogger.hpp"

#include <arpa/inet.h>
#include <fmt/core.h>
#include <netdb.h>
#include <unistd.h>

// Maximum size of UDP datagram: 65507 = (2^16 - 1) - 20 (UDP header) - 8 (IPv4 header)
#define UDP_MAX_SIZE 65507

static void logError_not_ready(const char *file, size_t line) {
    GLogger::Write(GLogger::error, file, line, "Socket not ready");
}

static void logError_strerror(const char *file, size_t line, int error_code) {
    GLogger::Write(GLogger::error, file, line, strerror(error_code));
}

static void logError_gai_strerror(const char *file, size_t line, int error_code) {
    GLogger::Write(GLogger::error, file, line, gai_strerror(error_code));
}

GUdpServer::GUdpServer(const std::string &local_addr, uint16_t local_port) {
    struct addrinfo hints, *res;

    bzero(&hints, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    auto s_addr{local_addr.c_str()};
    auto l_port{std::to_string(local_port)}; // avoid dangling pointer
    auto s_port{l_port.c_str()};

    if (!strlen(s_addr)) {
        s_addr = "0.0.0.0";
    }

    auto error_code{getaddrinfo(s_addr, s_port, &hints, &res)};
    if (error_code != 0) {
        logError_gai_strerror(__FILE__, __LINE__, error_code);
        goto free_and_exit;
    }

    m_socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (m_socket_fd == -1) {
        logError_strerror(__FILE__, __LINE__, errno);
        goto free_and_exit;
    }

    if (bind(m_socket_fd, res->ai_addr, res->ai_addrlen) == -1) {
        logError_strerror(__FILE__, __LINE__, errno);
        goto free_and_exit;
    }

    m_buffer   = new GBuffer(UDP_MAX_SIZE);
    m_is_ready = true;

free_and_exit:
    freeaddrinfo(res);
}

GUdpServer::~GUdpServer() {
    if (m_socket_fd != -1) {
        close(m_socket_fd);
    }

    if (m_buffer != nullptr) {
        delete m_buffer;
    }
}

bool GUdpServer::Receive() {
    if (!m_is_ready) {
        logError_not_ready(__FILE__, __LINE__);
        return false;
    }

    auto _addr = (struct sockaddr *)&m_peer_addr;
    auto bytes{recvfrom(m_socket_fd, m_buffer->data(), m_buffer->size(), 0, _addr, &m_peer_addr_len)};
    if (bytes == -1) {
        logError_strerror(__FILE__, __LINE__, errno);
        return false;
    }

    return m_buffer->SetUsed(static_cast<size_t>(bytes));
}

bool GUdpServer::Receive(GBuffer *dst_buffer) {
    if (!m_is_ready) {
        logError_not_ready(__FILE__, __LINE__);
        return false;
    }

    auto _addr = (struct sockaddr *)&m_peer_addr;
    auto bytes{recvfrom(m_socket_fd, dst_buffer->data(), dst_buffer->size(), 0, _addr, &m_peer_addr_len)};
    if (bytes == -1) {
        logError_strerror(__FILE__, __LINE__, errno);
        return false;
    }

    return m_buffer->SetUsed(static_cast<size_t>(bytes));
}

bool GUdpServer::Receive(void *dst_buffer, size_t *dst_bytes) {
    if (!m_is_ready) {
        logError_not_ready(__FILE__, __LINE__);
        return false;
    }

    auto _addr = (struct sockaddr *)&m_peer_addr;
    auto bytes{recvfrom(m_socket_fd, dst_buffer, UDP_MAX_SIZE, 0, _addr, &m_peer_addr_len)};
    if (bytes == -1) {
        logError_strerror(__FILE__, __LINE__, errno);
        return false;
    }

    *dst_bytes = static_cast<size_t>(bytes);
    return true;
}

bool GUdpServer::Send() {
    if (!m_is_ready) {
        logError_not_ready(__FILE__, __LINE__);
        return false;
    }

    auto _addr = (struct sockaddr *)&m_peer_addr;
    auto bytes{sendto(m_socket_fd, m_buffer->data(), m_buffer->used(), 0, _addr, m_peer_addr_len)};
    if (bytes == -1) {
        logError_strerror(__FILE__, __LINE__, errno);
        return false;
    }

    return true;
}

bool GUdpServer::Send(GBuffer *src_buffer) {
    if (!m_is_ready) {
        logError_not_ready(__FILE__, __LINE__);
        return false;
    }

    auto _addr = (struct sockaddr *)&m_peer_addr;
    auto bytes{sendto(m_socket_fd, src_buffer->data(), src_buffer->used(), 0, _addr, m_peer_addr_len)};
    if (bytes == -1) {
        logError_strerror(__FILE__, __LINE__, errno);
        return false;
    }

    return true;
}

bool GUdpServer::Send(void *src_buffer, size_t src_bytes) {
    if (!m_is_ready) {
        logError_not_ready(__FILE__, __LINE__);
        return false;
    }

    auto _addr = (struct sockaddr *)&m_peer_addr;
    auto bytes{sendto(m_socket_fd, src_buffer, src_bytes, 0, _addr, m_peer_addr_len)};
    if (bytes == -1) {
        logError_strerror(__FILE__, __LINE__, errno);
        return false;
    }

    return true;
}
