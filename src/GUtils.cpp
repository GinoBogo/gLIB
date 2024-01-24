////////////////////////////////////////////////////////////////////////////////
/// \file      GUtils.cpp
/// \version   0.2
/// \date      October 2022
/// \author    Gino Francesco Bogo (ᛊᛟᚱᚱᛖ ᛗᛖᚨ ᛁᛊᛏᚨᛗᛁ ᚨcᚢᚱᛉᚢ)
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GUtils.hpp"

/*
         HIGHER ADDRESS
    ┌──────────────────────┐
    │                      │
    │ Unmapped or Reserved │  Command-line argument & Environment Variables
    │                      │
    └──────────────────────┘ ....................
    ┌──────────────────────┐ ....................
    │    Stack Segment     │  Stack Frame
    │          ↓           │
    │                      │
    │                      │
    │                      │
    │          ↑           │
    │     Heap Segment     │  Dynamic Memory
    └──────────────────────┘ ....................
    ┌──────────────────────┐ ....................
    │  Uninitialized Data  │
    └──────────────────────┘  Data Segment
    ┌──────────────────────┐
    │   Initialized Data   │
    └──────────────────────┘ ....................
    ┌──────────────────────┐ ....................
    │                      │
    │     Text Segment     │  Executable Code
    │                      │
    └──────────────────────┘
         LOWER ADDRESS
 */

// *****************************************************************************
// *****************************************************************************
// SEGMENT Functions
// *****************************************************************************
// *****************************************************************************

// NOTE not all compilers support the __attribute__((fallthrough))
#define FALL_THROUGH /* fall through */

// Duff's Device (loop unrolling without leftover extra code)
#define DUFF_DEVICE(x) \
    case 7:            \
        _dst[i] = x;   \
        ++i;           \
        FALL_THROUGH;  \
    case 6:            \
        _dst[i] = x;   \
        ++i;           \
        FALL_THROUGH;  \
    case 5:            \
        _dst[i] = x;   \
        ++i;           \
        FALL_THROUGH;  \
    case 4:            \
        _dst[i] = x;   \
        ++i;           \
        FALL_THROUGH;  \
    case 3:            \
        _dst[i] = x;   \
        ++i;           \
        FALL_THROUGH;  \
    case 2:            \
        _dst[i] = x;   \
        ++i;           \
        FALL_THROUGH;  \
    case 1:            \
        _dst[i] = x;   \
        ++i;

void gb_memcpy(void* dst, void* src, size_t len) {

    char* _dst = (char*)dst;
    char* _src = (char*)src;

    size_t i   = 0;
    size_t div = len / 8;
    size_t rem = len % 8;

    switch (rem) {
        default:
            break;

        case 0:
            while (!(div == 0)) {

                --div;
                _dst[i] = _src[i];
                ++i;

                FALL_THROUGH;
                DUFF_DEVICE(_src[i]);
            };
    }
}

void gb_memset(void* dst, char val, size_t len) {

    char* _dst = (char*)dst;

    size_t i   = 0;
    size_t div = len / 8;
    size_t rem = len % 8;

    switch (rem) {
        default:
            break;

        case 0:
            while (!(div == 0)) {

                --div;
                _dst[i] = val;
                ++i;

                FALL_THROUGH;
                DUFF_DEVICE(val);
            };
    }
}

void gb_zeros(void* dst, size_t len) {

    char* _dst = (char*)dst;

    size_t i   = 0;
    size_t div = len / 8;
    size_t rem = len % 8;

    switch (rem) {
        default:
            break;

        case 0:
            while (!(div == 0)) {

                --div;
                _dst[i] = 0;
                ++i;

                FALL_THROUGH;
                DUFF_DEVICE(0);
            };
    }
}

/* *****************************************************************************
 End of File
 */
