#include <benchmark/benchmark.h>

#define A 0
#define B 1

static void BM_if_else_decision(benchmark::State &state) {
    auto buffer_A{new char[20]};
    auto buffer_B{new char[20]};
    auto buffer_id{A};

    for (auto _ : state) {
        char *focus;
        char *after;

        if (buffer_id == A) {
            focus = buffer_A;
            after = buffer_B;
        }
        else {
            focus = buffer_B;
            after = buffer_A;
        }

        benchmark::DoNotOptimize(*focus = 'G');
        benchmark::DoNotOptimize(*after = 'B');
        buffer_id = !buffer_id;
    }

    delete[] buffer_A;
    delete[] buffer_B;
}

static void BM_array_decision(benchmark::State &state) {
    auto buffer_A{new char[20]};
    auto buffer_B{new char[20]};
    auto buffer_id{A};

    struct TBuffer {
        char *focus;
        char *after;
    };

    TBuffer array[2];

    array[0].focus = buffer_A;
    array[0].after = buffer_B;
    array[1].focus = buffer_B;
    array[1].after = buffer_A;

    for (auto _ : state) {
        auto focus{array[buffer_id].focus};
        auto after{array[buffer_id].after};

        benchmark::DoNotOptimize(*focus = 'G');
        benchmark::DoNotOptimize(*after = 'B');
        buffer_id = !buffer_id;
    }

    delete[] buffer_A;
    delete[] buffer_B;
}

BENCHMARK(BM_if_else_decision);
BENCHMARK(BM_array_decision);

BENCHMARK_MAIN();