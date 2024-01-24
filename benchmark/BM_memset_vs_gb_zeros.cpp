#include "../src/GUtils.hpp"

#include <benchmark/benchmark.h>
#include <cstring>

static void BM_memset_decision(benchmark::State& state) {
    char buffer_A[1024];

    for (auto _ : state) {
        (void)memset(buffer_A, 0, sizeof(buffer_A));
    }
}

static void BM_gb_zeros_decision(benchmark::State& state) {
    char buffer_A[1024];

    for (auto _ : state) {
        gb_zeros(buffer_A, sizeof(buffer_A));
    }
}

BENCHMARK(BM_memset_decision);
BENCHMARK(BM_gb_zeros_decision);

BENCHMARK_MAIN();
