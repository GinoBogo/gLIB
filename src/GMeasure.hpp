////////////////////////////////////////////////////////////////////////////////
/// \file      GMeasure.hpp
/// \version   0.1
/// \date      March 2021
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include <chrono> // duration_cast, microseconds, milliseconds, nanoseconds, system_clock
#include <utility>

struct GMeasure {
    template <typename Func, typename... Args>
    static auto ms(Func func, Args&&...args) {
        auto T0 = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto T1 = std::chrono::system_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(T1 - T0).count();
    }

    template <typename Func, typename... Args>
    static auto us(Func func, Args&&...args) {
        auto T0 = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto T1 = std::chrono::system_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(T1 - T0).count();
    }

    template <typename Func, typename... Args>
    static auto ns(Func func, Args&&...args) {
        auto T0 = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto T1 = std::chrono::system_clock::now();

        return std::chrono::duration_cast<std::chrono::nanoseconds>(T1 - T0).count();
    }
};
