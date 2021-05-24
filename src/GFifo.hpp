////////////////////////////////////////////////////////////////////////////////
/// \file      GFifo.hpp
/// \version   0.1
/// \date      April 2021
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GFIFO_HPP
#define GFIFO_HPP

#include <condition_variable>
#include <mutex>

class GFifo {
    public:
    // clang-format off
    struct WAIT_IF_EMPTY    { bool _; };
    struct WAIT_IF_FULL     { bool _; };
    struct SIGNAL_NOT_EMPTY { bool _; };
    struct SIGNAL_NOT_FULL  { bool _; };
    // clang-format on

    GFifo(size_t bytes, size_t depth);

    ~GFifo();

    void ResetMetrics() __attribute__((cold));

    void Clear() __attribute__((cold));

    void Zeros() __attribute__((cold));

    bool Push(void *src_buffer, size_t src_bytes) __attribute__((hot));

    bool Pop(void *dst_buffer, size_t *dst_bytes) __attribute__((hot));

    template <typename T> void Acquire() {
        if constexpr (std::is_same_v<T, WAIT_IF_EMPTY>) {
            std::unique_lock<std::mutex> lock{m_mutex};
            while (!m_used) {
                m_event.wait(lock);
            }
        }
        if constexpr (std::is_same_v<T, WAIT_IF_FULL>) {
            std::unique_lock<std::mutex> lock{m_mutex};
            while (!m_free) {
                m_event.wait(lock);
            }
        }
    }

    template <typename T> void Release() {
        if constexpr (std::is_same_v<T, SIGNAL_NOT_EMPTY>) {
            std::lock_guard<std::mutex> lock{m_mutex};
            if (m_used) {
                m_event.notify_one();
            }
        }
        if constexpr (std::is_same_v<T, SIGNAL_NOT_FULL>) {
            std::lock_guard<std::mutex> lock{m_mutex};
            if (m_free) {
                m_event.notify_one();
            }
        }
    }

    size_t bytes() {
        return m_bytes - sizeof(size_t);
    }

    size_t depth() {
        return m_depth;
    }

    size_t overflow() {
        return m_overflow;
    }

    size_t underflow() {
        return m_underflow;
    }

    private:
    const size_t m_bytes;
    const size_t m_depth;
    size_t       m_iR;
    size_t       m_iW;
    char *       m_data;
    size_t       m_free;
    size_t       m_used;
    size_t       m_overflow;
    size_t       m_underflow;

    std::mutex              m_mutex;
    std::condition_variable m_event;

    void reset_metrics();

    void clear();

    void zeros();
};

#endif // GFIFO_HPP
