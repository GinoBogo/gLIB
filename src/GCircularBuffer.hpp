/* ************************************************************************** */
/*
    @file
        GCircularBuffer.hpp

    @date
        March, 2025

    @author
        Gino Bogo (ᛊᛟᚱᚱᛖ ᛗᛖᚨ ᛁᛊᛏᚨᛗᛁ ᚨcᚢᚱᛉᚢ)

    @copyright
        This file is released under the MIT license
*/
/* ************************************************************************** */

#ifndef GCIRCULARBUFFER_HPP
#define GCIRCULARBUFFER_HPP

#include <cstddef> // size_t
#include <vector>  // vector

// *****************************************************************************
// *****************************************************************************
// SEGMENT Class
// *****************************************************************************
// *****************************************************************************

template <typename T, size_t N>
class GCircularBuffer {
   private:
    std::vector<T> m_buffer;
    size_t         m_head{0};
    size_t         m_tail{0};
    size_t         m_size;
    bool           m_full{false};

   public:
    explicit GCircularBuffer() : m_buffer(N), m_size(N) {
        static_assert((N & (N - 1)) == 0, "Buffer size must be a power of 2");
    }

    bool push() {
        if (m_full) {
            return false;
        }

        m_buffer[m_head] = T{};

        m_head = (m_head + 1) & (m_size - 1); // valid for power of 2 sizes
        m_full = (m_head == m_tail);

        return true;
    }

    bool push(const T& item) {
        if (m_full) {
            return false;
        }

        m_buffer[m_head] = item;

        m_head = (m_head + 1) & (m_size - 1); // valid for power of 2 sizes
        m_full = (m_head == m_tail);

        return true;
    }

    T *pop() {
        if (is_empty()) {
            return nullptr;
        }

        T *item = &m_buffer[m_tail];

        m_tail = (m_tail + 1) & (m_size - 1); // valid for power of 2 sizes
        m_full = false;

        return item;
    }

    void clear() {
        m_head = 0;
        m_tail = 0;
        m_full = false;
    }

    bool resize(size_t new_count) {
        if (new_count > m_size) {
            return false;
        }

        size_t current_count = count();

        if (new_count > current_count) {
            size_t add_items = new_count - current_count;

            for (size_t i = 0; i < add_items; ++i) {
                if (!push()) {
                    return false;
                }
            }
        } else if (new_count < current_count) {
            size_t rem_items = current_count - new_count;

            for (size_t i = 0; i < rem_items; ++i) {
                if (pop() == nullptr) {
                    return false;
                }
            }
        }

        return true;
    }

    [[nodiscard]] bool contains(const T& item) const {
        for (size_t i = 0; i < count(); ++i) {
            if (at(i) == item) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] int find(const T& item) const {
        for (size_t i = 0; i < count(); ++i) {
            if (at(i) == item) {
                return (int)i;
            }
        }
        return -1;
    }

    [[nodiscard]] constexpr size_t count() const {
        return m_full ? m_size : (m_head >= m_tail ? m_head - m_tail : m_size + m_head - m_tail);
    }

    [[nodiscard]] inline bool is_empty() const { return (!m_full && (m_head == m_tail)); }

    [[nodiscard]] inline bool is_full() const { return m_full; }

    [[nodiscard]] constexpr size_t capacity() const { return m_size; }

    T& operator[](size_t index) {
        return m_buffer[(m_tail + index) & (m_size - 1)];
    } // valid for power of 2 sizes

    const T& at(size_t index) const {
        return m_buffer[(m_tail + index) & (m_size - 1)];
    } // valid for power of 2 sizes
};

#endif // GCIRCULARBUFFER_HPP

/*******************************************************************************
 End of File
 */
