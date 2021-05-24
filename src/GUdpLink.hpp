////////////////////////////////////////////////////////////////////////////////
/// \file      GUdpLink.hpp
/// \version   0.1
/// \date      January 2021
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GUDPLINK_HPP
#define GUDPLINK_HPP

#include "GUdpClient.hpp"
#include "GUdpServer.hpp"

#include <any>

namespace g_udp_link {
    struct MASTER {};
    struct SLAVE {};

    struct WorkerArgs {
        GBuffer * query_buffer;
        GBuffer * reply_buffer;
        std::any *custom_data;
    };

    typedef bool (*WorkerFunc)(WorkerArgs args);

} // namespace g_udp_link

template <typename T> class GUdpLink {
    public:
    GUdpLink(const std::string &addr, uint16_t port);
    ~GUdpLink();

    bool is_ready();

    // NOTE: use "func" to process the REPLY content
    bool SendQuery_WaitReply(g_udp_link::WorkerFunc func, g_udp_link::WorkerArgs args);

    // NOTE: use "func" to process the QUERY content
    bool WaitQuery_SendReply(g_udp_link::WorkerFunc func, g_udp_link::WorkerArgs args);

    private:
    void *m_udp_link{nullptr};
};

#endif // GUDPLINK_HPP