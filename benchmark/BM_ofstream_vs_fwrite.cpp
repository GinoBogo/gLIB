#include <benchmark/benchmark.h>
#include <cstring>
#include <fstream>

void filename_index(char *dst_filename, const char *src_filename, size_t index) {
    strcpy(dst_filename, src_filename);
    strcpy(dst_filename + strlen(dst_filename), "_000000.bin");
    auto pos{strlen(dst_filename) - 5};
    while (index > 0) {
        dst_filename[pos--] = '0' + (index % 10);
        index /= 10;
    }
}

static void BM_ofstream(benchmark::State &state) {
    auto filename{new char[1024]};
    auto buffer{new char[8e6]};
    auto index{0UL};

    for (auto _ : state) {
        filename_index(filename, "tx_samples", index++);
        auto stream{std::ofstream(filename, std::ios::binary)};
        stream.write(buffer, static_cast<std::streamsize>(state.range(0)));
        stream.close();
    }

    delete[] buffer;
    delete[] filename;
}

static void BM_fwrite(benchmark::State &state) {
    auto filename{new char[1024]};
    auto buffer{new char[8e6]};
    auto index{0UL};

    for (auto _ : state) {
        filename_index(filename, "tx_samples", index++);
        auto stream{fopen(filename, "wb")};
        fwrite(buffer, static_cast<size_t>(state.range(0)), 1, stream);
        fclose(stream);
    }

    delete[] buffer;
    delete[] filename;
}

BENCHMARK(BM_ofstream)->Arg(4000)->Arg(40000)->Arg(400000)->Arg(4000000);
BENCHMARK(BM_fwrite)->Arg(4000)->Arg(40000)->Arg(400000)->Arg(4000000);

BENCHMARK_MAIN();