////////////////////////////////////////////////////////////////////////////////
/// \file      GUdpLink.cpp
/// \version   0.1
/// \date      January 2021
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GUdpLink.hpp"

#include "GLogger.hpp"    // Write, error
#include "GUdpClient.hpp" // GUdpClient
#include "GUdpServer.hpp" // GUdpServer

#include <fmt/core.h> // format

using namespace g_udp_link;

static void logError_invalid_call(const char* file, size_t line, const char* mode, const char* func) {
    auto msg{fmt::format("\"{}\" cannot be called in {} mode", mode, func)};
    GLogger::Write(GLogger::error, file, line, msg);
}

template <typename T> GUdpLink<T>::GUdpLink(const std::string& addr, uint16_t port) {
    if constexpr (std::is_same_v<T, MASTER>) {
        m_udp_link = new GUdpClient(addr, port);
    }
    if constexpr (std::is_same_v<T, SLAVE>) {
        m_udp_link = new GUdpServer(addr, port);
    }
}

template <typename T> GUdpLink<T>::~GUdpLink() {
    if (m_udp_link != nullptr) {
        if constexpr (std::is_same_v<T, MASTER>) {
            delete (GUdpClient*)m_udp_link;
        }
        if constexpr (std::is_same_v<T, SLAVE>) {
            delete (GUdpServer*)m_udp_link;
        }
    }
}

template <typename T> bool GUdpLink<T>::is_ready() {
    auto check{false};
    if (m_udp_link != nullptr) {
        if constexpr (std::is_same_v<T, MASTER>) {
            check = ((GUdpClient*)m_udp_link)->is_ready();
        }
        if constexpr (std::is_same_v<T, SLAVE>) {
            check = ((GUdpServer*)m_udp_link)->is_ready();
        }
    }
    return check;
}

template <typename T> bool GUdpLink<T>::SendQuery_WaitReply(WorkerFunc func, WorkerArgs args) {
    auto check{false};
    if constexpr (std::is_same_v<T, MASTER>) {
        auto udp_client{(GUdpClient*)m_udp_link};

        check = udp_client->Send(args.query_buffer);
        check = check & udp_client->Receive(args.reply_buffer);
        check = check & func(args);
    }
    if constexpr (std::is_same_v<T, SLAVE>) {
        logError_invalid_call(__FILE__, __LINE__, "SLAVE", __func__);
    }
    return check;
}

template <typename T> bool GUdpLink<T>::WaitQuery_SendReply(WorkerFunc func, WorkerArgs args) {
    auto check{false};
    if constexpr (std::is_same_v<T, SLAVE>) {
        auto udp_server{(GUdpServer*)m_udp_link};

        check = udp_server->Receive(args.query_buffer);
        check = check & func(args);
        check = check & udp_server->Send(args.reply_buffer);
    }
    if constexpr (std::is_same_v<T, MASTER>) {
        logError_invalid_call(__FILE__, __LINE__, "MASTER", __func__);
    }
    return check;
}

template class GUdpLink<MASTER>;
template class GUdpLink<SLAVE>;
