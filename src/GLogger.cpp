////////////////////////////////////////////////////////////////////////////////
/// \file      GLogger.cpp
/// \version   0.4
/// \date      November 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GLogger.hpp"

#include <filesystem>
#include <fmt/chrono.h>
#include <fstream>
#include <iostream>

namespace GLogger {

    static bool is_open{false};

    static std::ofstream fout{};

    static const char *flags[6] = {"DEBUG", "ERROR", "FATAL", "INFO", "TRACE", "WARNING"};

    std::string GetDateTime() {
        auto tp{std::chrono::system_clock::now()};
        auto us{std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()) % 1'000'000};
        auto tt{std::chrono::system_clock::to_time_t(tp)};

        return fmt::format("{:%Y-%m-%d %H:%M:%S}.{:06d}", fmt::localtime(tt), us.count());
    }

    void Initialize(const std::string &filename) {
        is_open = fout.is_open();
        if (is_open) {
            LOG_WRITE(warning, "File stream already opened");
        }
        else {
            fout    = std::ofstream(filename);
            is_open = fout.is_open();
        }
    }

    void Write(Type type, const char *file, const size_t line, const std::string &message) {
        auto time{GetDateTime()};
        auto flag{flags[type]};
        auto name{std::filesystem::path(file).filename()};
        auto text{fmt::format("{} | {:<8} | {:>30} ({:04}) | {}", time, flag, name.string(), line, message)};

        if (!is_open) {
            fout    = std::ofstream(name.replace_extension(".log").string());
            is_open = fout.is_open();
        }

        using namespace std;
        cout << text << endl;
        fout << text << endl;

        cout.flush();
        fout.flush();
    }

    // WARNING: unsafe function
    char *AlignText(Alignment mode, const char *src, char *dst, size_t span, char filler) {
        if (src == nullptr || dst == nullptr) {
            return nullptr;
        }

        memset(dst, filler, span);
        size_t dst_shift = 0;
        size_t src_len   = strnlen(src, span);

        switch (mode) {
            case right:
                dst_shift = (span - src_len);
                break;

            case center:
                dst_shift = (span - src_len) / 2;
                break;

            case left:
            default:
                break;
        }

        src_len = std::min(src_len, span - dst_shift);
        memcpy(dst + dst_shift, src, src_len);
        dst[span] = 0;

        return dst;
    }
} // namespace GLogger