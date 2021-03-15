/// ============================================================================
/// File    : GMeasure.hpp
/// Version : 0.1
/// Date    : March 2021
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#include <chrono>
#include <utility>

struct GMeasure {
    template <typename Func, typename... Args> static auto ms(Func func, Args &&...args) {
        auto T0 = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto T1 = std::chrono::system_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(T1 - T0).count();
    }

    template <typename Func, typename... Args> static auto us(Func func, Args &&...args) {
        auto T0 = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto T1 = std::chrono::system_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(T1 - T0).count();
    }
};
