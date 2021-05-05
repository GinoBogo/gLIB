#include "GLogger.hpp"
#include "GPingPong.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <fstream>

void fileWriter(GPingPong::WorkerArgs *args) {
    if (args != nullptr) {
        char filename[4096];
        snprintf(filename, sizeof(filename), "tx_samples_%06lu.bin", static_cast<unsigned long>(*args->buffer_counter));
        auto stream{std::ofstream(filename, std::ios::binary)};

        stream.write(args->buffer->data(), static_cast<std::streamsize>(args->buffer->size()));
        stream.close();
    }
}

int main() {
    LOG_WRITE(trace, fmt::format("\"{}\" process STARTED", __func__));

    const auto chunk_bytes{200};
    const auto chunks_number{50};
    const auto loop_counter{300};

    auto pp_writer{GPingPong(chunk_bytes, chunks_number, GPingPong::WRITER, fileWriter)};

    auto src_buffer{new char[chunk_bytes]};

    size_t index{0};

    auto filler = [&index](char *data, size_t size) {
        for (decltype(size) i{0}; i < size; ++i) {
            auto rem{index++ % 11};
            data[i] = static_cast<char>(!rem ? '_' : ('0' - 1) + rem);
        }
    };

    for (auto i{0}; i < loop_counter; ++i) {
        filler(src_buffer, chunk_bytes);
        pp_writer.Write(src_buffer, chunk_bytes);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    delete[] src_buffer;

    LOG_WRITE(trace, fmt::format("\"{}\" process STOPPED", __func__));
    return 0;
}