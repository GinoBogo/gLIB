#include <benchmark/benchmark.h>
#include <cstddef>
#include <cstring>

static inline void* g_aligned_alloc(size_t alignment, size_t size) {
    // Alignment must be a power of two.
    if (alignment & (alignment - 1) || !size) {
        return nullptr;
    }

    // We need extra bytes to store the original value returned by malloc.
    if (alignment < sizeof(void*)) {
        alignment = sizeof(void*);
    }
    void* const malloc_ptr{std::malloc(size + alignment)};
    if (!malloc_ptr) {
        return nullptr;
    }

    // Align to the requested value, leaving room for the original malloc value.
    void* const aligned_ptr{(void*)(((uintptr_t)malloc_ptr + alignment) & -alignment)};

    // Store the original malloc value where it can be found by the free function.
    ((void**)aligned_ptr)[-1] = malloc_ptr;
    return aligned_ptr;
}

static inline void g_free(void* aligned_ptr) {
    std::free(((void**)aligned_ptr)[-1]);
}

const auto chunk_bytes{64000};
const auto chunks_number{200};

static void BM_malloc_AND_memcpy(benchmark::State& state) {
    const auto src_size{chunk_bytes};
    const auto dst_size{chunk_bytes * chunks_number};

    auto src_buffer{static_cast<char*>(std::malloc(src_size))};
    auto dst_buffer{static_cast<char*>(std::malloc(dst_size))};

    for (auto _ : state) {
        for (auto i{0}; i < chunks_number; ++i) {
            state.PauseTiming();
            std::memset(src_buffer, i, src_size);
            state.ResumeTiming();

            std::memcpy(dst_buffer + (i * src_size), src_buffer, src_size);
        }
    }

    std::free(dst_buffer);
    std::free(src_buffer);
}

static void BM_new_operator_AND_memcpy(benchmark::State& state) {
    const auto src_size{chunk_bytes};
    const auto dst_size{chunk_bytes * chunks_number};

    auto src_buffer{new char[src_size]};
    auto dst_buffer{new char[dst_size]};

    for (auto _ : state) {
        for (auto i{0}; i < chunks_number; ++i) {
            state.PauseTiming();
            std::memset(src_buffer, i, src_size);
            state.ResumeTiming();

            std::memcpy(dst_buffer + (i * src_size), src_buffer, src_size);
        }
    }

    delete[] src_buffer;
    delete[] dst_buffer;
}

static void BM_g_aligned_alloc_AND_memcpy(benchmark::State& state) {
    const auto src_size{chunk_bytes};
    const auto dst_size{chunk_bytes * chunks_number};

    auto src_buffer{static_cast<char*>(g_aligned_alloc(64, src_size))};
    auto dst_buffer{static_cast<char*>(g_aligned_alloc(64, dst_size))};

    for (auto _ : state) {
        for (auto i{0}; i < chunks_number; ++i) {
            state.PauseTiming();
            std::memset(src_buffer, i, src_size);
            state.ResumeTiming();

            std::memcpy(dst_buffer + (i * src_size), src_buffer, src_size);
        }
    }

    g_free(dst_buffer);
    g_free(src_buffer);
}

BENCHMARK(BM_malloc_AND_memcpy);
BENCHMARK(BM_new_operator_AND_memcpy);
BENCHMARK(BM_g_aligned_alloc_AND_memcpy);

BENCHMARK_MAIN();
