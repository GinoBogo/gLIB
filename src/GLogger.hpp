////////////////////////////////////////////////////////////////////////////////
/// \file      GLogger.hpp
/// \version   0.4
/// \date      November 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GLOGGER_HPP
#define GLOGGER_HPP

#include <string>

#define LOG_WRITE(type, message) GLogger::Write(GLogger::type, __FILE__, __LINE__, message)

namespace GLogger {

    enum Type { debug, error, fatal, info, trace, warning };

    void Initialize(const std::string& filename);

    void Write(Type type, const std::string& file, size_t line, const std::string& message);

} // namespace GLogger

#endif // GLOGGER_HPP
