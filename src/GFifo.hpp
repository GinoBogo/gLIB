/// ============================================================================
/// File    : GFifo.hpp
/// Version : 0.1
/// Date    : April 2021
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GFIFO_HPP
#define GFIFO_HPP

#include <condition_variable>
#include <mutex>

class GFifo {
    public:
    enum AcquireCondition { WAIT_IF_EMPTY, WAIT_IF_FULL };
    enum ReleaseCondition { SIGNAL_NOT_EMPTY, SIGNAL_NOT_FULL };

    GFifo(size_t bytes, size_t depth);

    ~GFifo();

    void Clear() __attribute__((cold));

    void Zeros() __attribute__((cold));

    bool Push(void *src_buffer, size_t src_bytes) __attribute__((hot));

    bool Pop(void *dst_buffer, size_t *dst_bytes) __attribute__((hot));

    void Acquire(AcquireCondition condition) {
        switch (condition) {
            case WAIT_IF_EMPTY: {
                std::unique_lock<std::mutex> lock{m_mutex};
                while (!m_used) {
                    m_event.wait(lock);
                }
            } break;

            case WAIT_IF_FULL: {
                std::unique_lock<std::mutex> lock{m_mutex};
                while (!m_free) {
                    m_event.wait(lock);
                }
            } break;

            default:
                break;
        }
    }

    void Release(ReleaseCondition condition) {
        switch (condition) {
            case SIGNAL_NOT_EMPTY: {
                std::lock_guard<std::mutex> lock{m_mutex};
                if (m_used) {
                    m_event.notify_one();
                }
            } break;

            case SIGNAL_NOT_FULL: {
                std::lock_guard<std::mutex> lock{m_mutex};
                if (m_free) {
                    m_event.notify_one();
                }
            } break;

            default:
                break;
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
};

#endif // GFIFO_HPP
