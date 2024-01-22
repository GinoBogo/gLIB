////////////////////////////////////////////////////////////////////////////////
/// \file      GPtr.hpp
/// \version   0.1
/// \date      May 2021
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GPTR_HPP
#define GPTR_HPP

#include <type_traits> // is_same_v, is_void_v

namespace G::Ptr {
    // clang-format off
    struct K_ARRAY  { bool _; };
    struct K_OBJECT { bool _; };
    // clang-format on
} // namespace G::Ptr

template <typename T, typename K = G::Ptr::K_ARRAY> class GPtr {
  public:
    GPtr(T* ptr) {
        m_ptr = ptr;
    }

    ~GPtr() {
        static_assert(!std::is_void_v<T>, "can't delete pointer to incomplete type");

        if constexpr (std::is_same_v<K, G::Ptr::K_ARRAY>) {
            delete[] m_ptr;
        }
        else {
            delete m_ptr;
        }
    }

    T* operator()() const {
        return m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }

    T& operator*() const {
        return *m_ptr;
    }

  private:
    T* m_ptr;
};

#endif // GPTR_HPP
