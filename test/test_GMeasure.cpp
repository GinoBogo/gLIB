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

    fmt::print(" - Factorial({}) = {}\n", number, result);
}

int main() {
    std::function<void(int, int)> func = factorial_loop;

    auto loop    = 20000;
    auto elapsed = GMeasure::ns(func, loop, 23);

    fmt::print(" - Elapsed time = {} ns\n", elapsed / (double)loop);

    return 0;
}