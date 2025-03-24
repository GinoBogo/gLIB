////////////////////////////////////////////////////////////////////////////////
/// \file      GPingPong.cpp
/// \version   0.1
/// \date      October 2020
/// \author    Gino Francesco Bogo (ᛊᛟᚱᚱᛖ ᛗᛖᚨ ᛁᛊᛏᚨᛗᛁ ᚨcᚢᚱᛉᚢ)
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GPingPong.hpp"

#include <fmt/core.h> // format

#include "GLogger.hpp"         // LOG_WRITE, error, info, trace
#include "GThreadPriority.hpp" // get_priority, get_priority_range, set_priority

#define PING 0
#define PONG 1

GPingPong::GPingPong(
    size_t chunk_bytes, size_t chunks_number, StreamType stream_type, WorkerFunc worker_func, std::any *user_data)
    : m_chunk_bytes{chunk_bytes}, m_chunks_number{chunks_number}, m_stream_type{stream_type} {
    m_buffer_pair[0].focus = new GBuffer(m_chunk_bytes * m_chunks_number);
    m_buffer_pair[0].after = new GBuffer(m_chunk_bytes * m_chunks_number);
    m_buffer_pair[1].focus = m_buffer_pair[0].after;
    m_buffer_pair[1].after = m_buffer_pair[0].focus;
    m_buffer_pair_id       = PING;
    m_buffer_counter       = 0;
    m_thread_exit          = false;
    m_thread_busy          = false;

    m_thread_args.thread_exit  = &m_thread_exit;
    m_thread_args.thread_busy  = &m_thread_busy;
    m_thread_args.thread_mutex = &m_thread_mutex;
    m_thread_args.thread_order = &m_thread_order;

    m_worker_args.buffer         = nullptr;
    m_worker_args.buffer_counter = &m_buffer_counter;
    m_worker_args.user_data      = user_data;
    m_worker_func                = worker_func;

    auto t_loop = [](ThreadArgs *t_args, WorkerArgs *w_args, WorkerFunc w_func) {
        while (!*t_args->thread_exit) {
            std::unique_lock<std::mutex> lock(*t_args->thread_mutex);
            t_args->thread_order->wait(lock, [t_args] { return *t_args->thread_exit || *t_args->thread_busy; });

            if (!*t_args->thread_exit) {
                w_func(w_args);
                ++(*w_args->buffer_counter);
            }
            *t_args->thread_busy = false;
        }
    };

    m_thread_loop = std::thread(t_loop, &m_thread_args, &m_worker_args, m_worker_func);
}

GPingPong::~GPingPong() {
    m_thread_exit = true;
    m_thread_order.notify_one();

    if (m_thread_loop.joinable()) {
        m_thread_loop.join();
    }

    delete m_buffer_pair[0].focus;
    delete m_buffer_pair[0].after;
}

int GPingPong::GetThreadPriority() {
    return GThreadPriority::get_priority(m_thread_loop);
}

bool GPingPong::SetThreadPriority(int priority) {
    int min_priority, max_priority;
    GThreadPriority::get_priority_range(m_thread_loop, &min_priority, &max_priority);

    if (min_priority <= priority and priority <= max_priority) {
        if (GThreadPriority::set_priority(m_thread_loop, priority)) {
            LOG_WRITE(trace, "Thread priority has been changed");
            return true;
        } else {
            LOG_WRITE(error, "Unable to change the thread priority");
        }
    } else {
        LOG_WRITE(error, "Wrong thread priority value");
        LOG_WRITE(info, fmt::format("Valid thread priority values: [{} → {}]", min_priority, max_priority));
    }
    return false;
}

bool GPingPong::Read(void *dst_buffer, size_t dst_bytes) {
    if (m_stream_type == READER && dst_buffer != nullptr && dst_bytes == m_chunk_bytes) {
        return UseNext<bool>(dst_buffer, dst_bytes);
    }
    LOG_WRITE(error, fmt::format("Wrong \"{}\" function usage", __func__));
    return false;
}

bool GPingPong::Write(void *src_buffer, size_t src_bytes) {
    if (m_stream_type == WRITER && src_buffer != nullptr && src_bytes == m_chunk_bytes) {
        return UseNext<long>(src_buffer, src_bytes);
    }
    LOG_WRITE(error, fmt::format("Wrong \"{}\" function usage", __func__));
    return false;
}

template <typename T>
bool GPingPong::UseNext(void *buffer, size_t bytes) {
    auto error_raised{false};
    auto toggle_buffer{false};

    auto _focus{m_buffer_pair[m_buffer_pair_id].focus};
    auto _after{m_buffer_pair[m_buffer_pair_id].after};

    if constexpr (std::is_same_v<T, bool>) {
        error_raised = !_focus->ReadNext(buffer, bytes, &toggle_buffer);
    } else {
        error_raised = !_focus->WriteNext(buffer, bytes, &toggle_buffer);
    }
    if (toggle_buffer) {
        {
            std::lock_guard<std::mutex> lock(m_thread_mutex);
            if (!m_thread_busy) {
                m_worker_args.buffer = _focus;
                m_thread_busy        = true;
            } else {
                error_raised = true;
                LOG_WRITE(error, "<producer> faster than <consumer>");
            }
        }
        if (!error_raised) {
            m_thread_order.notify_one();
        }

        _after->Clear();
        m_buffer_pair_id = !m_buffer_pair_id;
    }
    return !error_raised;
}
