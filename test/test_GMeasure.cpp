#include "GLogger.hpp"
#include "GMeasure.hpp"

#include <fmt/core.h>
#include <functional>

int multiply(int x, int res[], int res_size) {
    int carry = 0;

    for (int i = 0; i < res_size; i++) {
        int prod = res[i] * x + carry;
        res[i]   = prod % 10;
        carry    = prod / 10;
    }

    while (carry) {
        res[res_size] = carry % 10;
        carry         = carry / 10;
        res_size++;
    }
    return res_size;
}

std::string factorial(int n) {
    std::string value = "";

    int res[2000];

    res[0]       = 1;
    int res_size = 1;

    for (auto x = 2; x <= n; x++) {
        res_size = multiply(x, res, res_size);
    }

    for (int i = res_size - 1; i >= 0; i--) {
        value += std::to_string(res[i]);
    }

    return value;
}

void function_loop(int loop, int number, std::string *result) {
    while (loop-- > 0) {
        *result = factorial(number);
    }
}

int main() {
    LOG_WRITE(trace, fmt::format("\"{}\" process STARTED", __func__));

    std::function<void(int, int, std::string *)> func = function_loop;

    auto loop    = 80000;
    auto number  = 69;
    auto result  = std::string("");
    auto elapsed = GMeasure::ns(func, loop, number, &result);

    LOG_WRITE(debug, fmt::format(" - Factorial({}) = {}", number, result));
    LOG_WRITE(debug, fmt::format(" - Elapsed time = {} ns", elapsed / (double)loop));

    LOG_WRITE(trace, fmt::format("\"{}\" process STOPPED", __func__));
    return 0;
}