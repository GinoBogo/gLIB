#include <benchmark/benchmark.h>
#include <string.h>

void filename_index(char* dst_filename, const char* src_filename, size_t index) {
    strcpy(dst_filename, src_filename);
    strcpy(dst_filename + strlen(dst_filename), "_000000.bin");
    auto pos{strlen(dst_filename) - 5};
    while (index > 0) {
        dst_filename[pos--]  = '0' + (index % 10);
        index               /= 10;
    }
}

static void BM_filename_snprintf(benchmark::State& state) {
    for (auto _ : state) {
        auto N{static_cast<size_t>(state.range(0))};
        for (size_t index = 0; index < N; ++index) {
            char filename[4096];
            snprintf(filename, sizeof(filename), "tx_samples_%06zu.bin", index);
        }
    }
}

static void BM_filename_strcpy(benchmark::State& state) {
    for (auto _ : state) {
        auto N{static_cast<size_t>(state.range(0))};
        for (size_t index = 0; index < N; ++index) {
            char filename[4096];
            filename_index(filename, "tx_samples", index);
        }
    }
}

BENCHMARK(BM_filename_snprintf)->Arg(100)->Arg(1000)->Arg(10000);
BENCHMARK(BM_filename_strcpy)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_MAIN();
