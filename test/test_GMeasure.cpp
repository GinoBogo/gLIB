#include "GLogger.hpp"
#include "GMeasure.hpp"

#include <fmt/core.h>
#include <functional>

int factorial(int n) {
    if (n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

void factorial_loop(int loop, int number) {
    auto result = 0;

    while (loop-- > 0) {
        result = factorial(number);
    }

    LOG_WRITE(debug, fmt::format(" - Factorial({}) = {}", number, result));
}

int main() {
    LOG_WRITE(trace, fmt::format("\"{}\" process STARTED", __func__));

    std::function<void(int, int)> func = factorial_loop;

    auto loop    = 20000;
    auto elapsed = GMeasure::ns(func, loop, 23);

    LOG_WRITE(debug, fmt::format(" - Elapsed time = {} ns", elapsed / (double)loop));

    LOG_WRITE(trace, fmt::format("\"{}\" process STOPPED", __func__));
    return 0;
}