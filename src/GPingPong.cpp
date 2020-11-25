/// ============================================================================
/// File    : GPingPong.cpp
/// Version : 0.1
/// Date    : October 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#include "GPingPong.hpp"

#define PING 0
#define PONG 1

GPingPong::GPingPong(size_t chunk_bytes, size_t chunks_number, StreamType stream_type, WorkerFunc worker_func)
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

void GPingPong::Read(void *dst_buffer, size_t dst_bytes) {
    if (m_stream_type == READER && dst_buffer != nullptr && dst_bytes == m_chunk_bytes) {
        UseNext<bool>(dst_buffer, dst_bytes);
    }
}

void GPingPong::Write(void *src_buffer, size_t src_bytes) {
    if (m_stream_type == WRITER && src_buffer != nullptr && src_bytes == m_chunk_bytes) {
        UseNext<long>(src_buffer, src_bytes);
    }
}

template <typename T> void GPingPong::UseNext(void *buffer, size_t bytes) {
    auto _focus{m_buffer_pair[m_buffer_pair_id].focus};
    auto _after{m_buffer_pair[m_buffer_pair_id].after};

    bool toggle_buffer;
    if constexpr (std::is_same_v<T, bool>) {
        _focus->ReadNext(buffer, bytes, &toggle_buffer);
    }
    else {
        _focus->WriteNext(buffer, bytes, &toggle_buffer);
    }
    if (toggle_buffer) {
        auto error_raised{false};
        {
            std::lock_guard<std::mutex> lock(m_thread_mutex);
            if (!m_thread_busy) {
                m_worker_args.buffer = _focus;
                m_thread_busy        = true;
            }
            else {
                error_raised = true;
            }
        }
        if (!error_raised) m_thread_order.notify_one();

        _after->Clear();
        m_buffer_pair_id = !m_buffer_pair_id;
    }
}
