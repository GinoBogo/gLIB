////////////////////////////////////////////////////////////////////////////////
/// \file      GLogger.hpp
/// \version   0.4
/// \date      November 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GLOGGER_HPP
#define GLOGGER_HPP

#include <cstdio> // snprintf
#include <string> // string

#define LOG_MSG_MAXLEN                512
#define LOG_TYPE(type)                GLogger::type, __FILE__, __LINE__
#define LOG_WRITE(type, message)      GLogger::Write(LOG_TYPE(type), message)
#define LOG_FORMAT(type, format, ...) GLogger::Format(LOG_TYPE(type), format, __VA_ARGS__)

namespace GLogger {

    enum Type { debug, error, fatal, info, trace, warning };

    void Initialize(const std::string &filename);

    void Write(Type type, const char *file, size_t line, const std::string &message);

    template <class... Args> void Format(Type type, const char *file, size_t line, const char *format, Args... args) {
        char msg[LOG_MSG_MAXLEN];
        snprintf(msg, sizeof msg, format, args...);
        Write(type, file, line, msg);
    }

} // namespace GLogger

#endif // GLOGGER_HPP