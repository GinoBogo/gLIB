#include "GFilePipe.hpp"
#include "GLogger.hpp"

#include <fmt/core.h>

int main() {
    LOG_WRITE(trace, fmt::format("\"{}\" process STARTED", __func__));

    const auto chunk_bytes{200};
    const auto chunks_number{50};
    const auto loop_counter{300};

    auto file_pipe{GFilePipe("tx_samples_{:04}.bin", chunk_bytes, chunks_number, GPingPong::WRITER)};

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
        file_pipe.Write(src_buffer, chunk_bytes);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    delete[] src_buffer;

    LOG_WRITE(trace, fmt::format("\"{}\" process STOPPED", __func__));
    return 0;
}