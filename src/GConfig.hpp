////////////////////////////////////////////////////////////////////////////////
/// \file      GConfig.hpp
/// \version   0.2
/// \date      November 2020
/// \author    Gino Francesco Bogo (ᛊᛟᚱᚱᛖ ᛗᛖᚨ ᛁᛊᛏᚨᛗᛁ ᚨcᚢᚱᛉᚢ)
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GCONFIG_HPP
#define GCONFIG_HPP

#include "GOptions.hpp" // GOptions

class GConfig {
   public:
    bool ReadOptions(const std::string& filename);

    bool WriteOptions(const std::string& filename);

    auto options() { return &m_options; }

   private:
    GOptions m_options;
};

#endif // GCONFIG_HPP
