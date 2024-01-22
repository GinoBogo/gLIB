////////////////////////////////////////////////////////////////////////////////
/// \file      GFilePipe.cpp
/// \version   0.2
/// \date      December 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GFilePipe.hpp"

#include "GLogger.hpp" // LOG_WRITE, error

#include <fmt/core.h> // format
#include <fstream>    // ifstream, ofstream

namespace g_file_pipe {
    void fileReader(GPingPong::WorkerArgs* args) {
        if (args != nullptr) {
            auto filename{fmt::format(std::any_cast<std::string>(*args->user_data), *args->buffer_counter)};

            auto stream{std::ifstream(filename, std::ios::binary)};
            auto dst_data{args->buffer->data()};
            auto dst_size{args->buffer->size()};
            stream.read(dst_data, static_cast<std::streamsize>(dst_size));
            stream.close();
        }
    }

    void fileWriter(GPingPong::WorkerArgs* args) {
        if (args != nullptr) {
            auto filename{fmt::format(std::any_cast<std::string>(*args->user_data), *args->buffer_counter)};

            auto stream{std::ofstream(filename, std::ios::binary)};
            auto dst_data{args->buffer->data()};
            auto dst_size{args->buffer->size()};
            stream.write(dst_data, static_cast<std::streamsize>(dst_size));
            stream.close();
        }
    }
} // namespace g_file_pipe

GFilePipe::GFilePipe(const std::string& filename_fmt, size_t chunk_bytes, size_t chunks_number, GPingPong::StreamType stream_type) {
    m_user_data = filename_fmt;

    switch (stream_type) {
        case GPingPong::READER:
            m_ping_pong = new GPingPong(chunk_bytes, chunks_number, GPingPong::READER, g_file_pipe::fileReader, &m_user_data);
            break;
        case GPingPong::WRITER:
            m_ping_pong = new GPingPong(chunk_bytes, chunks_number, GPingPong::WRITER, g_file_pipe::fileWriter, &m_user_data);
            break;
        default:
            m_ping_pong = nullptr;
            LOG_WRITE(error, "Wrong \"stream_type\" value");
            break;
    }
}

GFilePipe::~GFilePipe() {
    delete m_ping_pong;
}
