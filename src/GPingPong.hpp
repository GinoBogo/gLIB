/// ============================================================================
/// File    : GPingPong.hpp
/// Version : 0.1
/// Date    : October 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GPINGPONG_HPP
#define GPINGPONG_HPP

#include "GBuffer.hpp"

#include <condition_variable>
#include <thread>

class GPingPong {
    public:
    enum StreamType { READER, WRITER };

    struct WorkerArgs {
        GBuffer *buffer;
        size_t * buffer_counter;
    };

    typedef void (*WorkerFunc)(WorkerArgs *args);

    GPingPong(size_t chunk_bytes, size_t chunks_number, StreamType stream_type, WorkerFunc worker_func);

    ~GPingPong();

    void Read(void *dst_buffer, size_t dst_bytes);

    void Write(void *src_buffer, size_t src_bytes);

    private:
    struct ThreadArgs {
        bool *                   thread_exit;
        bool *                   thread_busy;
        std::mutex *             thread_mutex;
        std::condition_variable *thread_order;
    };

    struct TBufferPair {
        GBuffer *focus;
        GBuffer *after;
    };

    const size_t            m_chunk_bytes;
    const size_t            m_chunks_number;
    const StreamType        m_stream_type;
    TBufferPair             m_buffer_pair[2];
    int                     m_buffer_pair_id;
    size_t                  m_buffer_counter;
    bool                    m_thread_exit;
    bool                    m_thread_busy;
    std::mutex              m_thread_mutex;
    std::condition_variable m_thread_order;
    std::thread             m_thread_loop;
    ThreadArgs              m_thread_args;
    WorkerArgs              m_worker_args;
    WorkerFunc              m_worker_func;
};

#endif // GPINGPONG_HPP