////////////////////////////////////////////////////////////////////////////////
/// \file      GUtils.hpp
/// \version   0.2
/// \date      October 2022
/// \author    Gino Francesco Bogo (ᛊᛟᚱᚱᛖ ᛗᛖᚨ ᛁᛊᛏᚨᛗᛁ ᚨcᚢᚱᛉᚢ)
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#ifndef GB_UTILS_H
#define GB_UTILS_H

#include <cstddef> // size_t

// *****************************************************************************
// *****************************************************************************
// SEGMENT Macros
// *****************************************************************************
// *****************************************************************************

// MASK-HELPER macros
#define MASK_FROM_2_BOOL(b2, b1)     ((uint8_t)(b1) | ((uint8_t)(b2) << 1))
#define MASK_FROM_3_BOOL(b3, b2, b1) ((uint8_t)(b1) | ((uint8_t)(b2) << 1) | ((uint8_t)(b3) << 2))
#define MASK_FROM_4_BOOL(b4, b3, b2, b1) \
    ((uint8_t)(b1) | ((uint8_t)(b2) << 1) | ((uint8_t)(b3) << 2) | ((uint8_t)(b4) << 3))

// NIBBLE macros
#define N_0000 0
#define N_0001 1
#define N_0010 2
#define N_0011 3
#define N_0100 4
#define N_0101 5
#define N_0110 6
#define N_0111 7
#define N_1000 8
#define N_1001 9
#define N_1010 A
#define N_1011 B
#define N_1100 C
#define N_1101 D
#define N_1110 E
#define N_1111 F

// BYTE macros
#define B_00000000 00
#define B_00000001 01
#define B_00000010 02
#define B_00000011 03
#define B_00000100 04
#define B_00000101 05
#define B_00000110 06
#define B_00000111 07
#define B_00001000 08
#define B_00001001 09
#define B_00001010 0A
#define B_00001011 0B
#define B_00001100 0C
#define B_00001101 0D
#define B_00001110 0E
#define B_00001111 0F
#define B_00010000 10
#define B_00010001 11
#define B_00010010 12
#define B_00010011 13
#define B_00010100 14
#define B_00010101 15
#define B_00010110 16
#define B_00010111 17
#define B_00011000 18
#define B_00011001 19
#define B_00011010 1A
#define B_00011011 1B
#define B_00011100 1C
#define B_00011101 1D
#define B_00011110 1E
#define B_00011111 1F
#define B_00100000 20
#define B_00100001 21
#define B_00100010 22
#define B_00100011 23
#define B_00100100 24
#define B_00100101 25
#define B_00100110 26
#define B_00100111 27
#define B_00101000 28
#define B_00101001 29
#define B_00101010 2A
#define B_00101011 2B
#define B_00101100 2C
#define B_00101101 2D
#define B_00101110 2E
#define B_00101111 2F
#define B_00110000 30
#define B_00110001 31
#define B_00110010 32
#define B_00110011 33
#define B_00110100 34
#define B_00110101 35
#define B_00110110 36
#define B_00110111 37
#define B_00111000 38
#define B_00111001 39
#define B_00111010 3A
#define B_00111011 3B
#define B_00111100 3C
#define B_00111101 3D
#define B_00111110 3E
#define B_00111111 3F
#define B_01000000 40
#define B_01000001 41
#define B_01000010 42
#define B_01000011 43
#define B_01000100 44
#define B_01000101 45
#define B_01000110 46
#define B_01000111 47
#define B_01001000 48
#define B_01001001 49
#define B_01001010 4A
#define B_01001011 4B
#define B_01001100 4C
#define B_01001101 4D
#define B_01001110 4E
#define B_01001111 4F
#define B_01010000 50
#define B_01010001 51
#define B_01010010 52
#define B_01010011 53
#define B_01010100 54
#define B_01010101 55
#define B_01010110 56
#define B_01010111 57
#define B_01011000 58
#define B_01011001 59
#define B_01011010 5A
#define B_01011011 5B
#define B_01011100 5C
#define B_01011101 5D
#define B_01011110 5E
#define B_01011111 5F
#define B_01100000 60
#define B_01100001 61
#define B_01100010 62
#define B_01100011 63
#define B_01100100 64
#define B_01100101 65
#define B_01100110 66
#define B_01100111 67
#define B_01101000 68
#define B_01101001 69
#define B_01101010 6A
#define B_01101011 6B
#define B_01101100 6C
#define B_01101101 6D
#define B_01101110 6E
#define B_01101111 6F
#define B_01110000 70
#define B_01110001 71
#define B_01110010 72
#define B_01110011 73
#define B_01110100 74
#define B_01110101 75
#define B_01110110 76
#define B_01110111 77
#define B_01111000 78
#define B_01111001 79
#define B_01111010 7A
#define B_01111011 7B
#define B_01111100 7C
#define B_01111101 7D
#define B_01111110 7E
#define B_01111111 7F
#define B_10000000 80
#define B_10000001 81
#define B_10000010 82
#define B_10000011 83
#define B_10000100 84
#define B_10000101 85
#define B_10000110 86
#define B_10000111 87
#define B_10001000 88
#define B_10001001 89
#define B_10001010 8A
#define B_10001011 8B
#define B_10001100 8C
#define B_10001101 8D
#define B_10001110 8E
#define B_10001111 8F
#define B_10010000 90
#define B_10010001 91
#define B_10010010 92
#define B_10010011 93
#define B_10010100 94
#define B_10010101 95
#define B_10010110 96
#define B_10010111 97
#define B_10011000 98
#define B_10011001 99
#define B_10011010 9A
#define B_10011011 9B
#define B_10011100 9C
#define B_10011101 9D
#define B_10011110 9E
#define B_10011111 9F
#define B_10100000 A0
#define B_10100001 A1
#define B_10100010 A2
#define B_10100011 A3
#define B_10100100 A4
#define B_10100101 A5
#define B_10100110 A6
#define B_10100111 A7
#define B_10101000 A8
#define B_10101001 A9
#define B_10101010 AA
#define B_10101011 AB
#define B_10101100 AC
#define B_10101101 AD
#define B_10101110 AE
#define B_10101111 AF
#define B_10110000 B0
#define B_10110001 B1
#define B_10110010 B2
#define B_10110011 B3
#define B_10110100 B4
#define B_10110101 B5
#define B_10110110 B6
#define B_10110111 B7
#define B_10111000 B8
#define B_10111001 B9
#define B_10111010 BA
#define B_10111011 BB
#define B_10111100 BC
#define B_10111101 BD
#define B_10111110 BE
#define B_10111111 BF
#define B_11000000 C0
#define B_11000001 C1
#define B_11000010 C2
#define B_11000011 C3
#define B_11000100 C4
#define B_11000101 C5
#define B_11000110 C6
#define B_11000111 C7
#define B_11001000 C8
#define B_11001001 C9
#define B_11001010 CA
#define B_11001011 CB
#define B_11001100 CC
#define B_11001101 CD
#define B_11001110 CE
#define B_11001111 CF
#define B_11010000 D0
#define B_11010001 D1
#define B_11010010 D2
#define B_11010011 D3
#define B_11010100 D4
#define B_11010101 D5
#define B_11010110 D6
#define B_11010111 D7
#define B_11011000 D8
#define B_11011001 D9
#define B_11011010 DA
#define B_11011011 DB
#define B_11011100 DC
#define B_11011101 DD
#define B_11011110 DE
#define B_11011111 DF
#define B_11100000 E0
#define B_11100001 E1
#define B_11100010 E2
#define B_11100011 E3
#define B_11100100 E4
#define B_11100101 E5
#define B_11100110 E6
#define B_11100111 E7
#define B_11101000 E8
#define B_11101001 E9
#define B_11101010 EA
#define B_11101011 EB
#define B_11101100 EC
#define B_11101101 ED
#define B_11101110 EE
#define B_11101111 EF
#define B_11110000 F0
#define B_11110001 F1
#define B_11110010 F2
#define B_11110011 F3
#define B_11110100 F4
#define B_11110101 F5
#define B_11110110 F6
#define B_11110111 F7
#define B_11111000 F8
#define B_11111001 F9
#define B_11111010 FA
#define B_11111011 FB
#define B_11111100 FC
#define B_11111101 FD
#define B_11111110 FE
#define B_11111111 FF

#define N2H_(bits) N_##bits
#define N2H(bits)  N2H_(bits)
#define B2H_(bits) B_##bits
#define B2H(bits)  B2H_(bits)
#define CON_(a, b) a##b
#define CON(a, b)  CON_(a, b)
#define HEX_(n)    0x##n
#define HEX(n)     HEX_(n)

#define WORD_04(a)          HEX(N2H(a))
#define WORD_08(a)          HEX(B2H(a))
#define WORD_16(a, b)       HEX(CON(B2H(a), B2H(b)))
#define WORD_32(a, b, c, d) HEX(CON(CON(B2H(a), B2H(b)), CON(B2H(c), B2H(d))))

// BIT-WISE macros
// clang-format off
#define SWAP_WORD_08(data) (                       \
    (((uint8_t)(data) & WORD_08(10000000)) >> 7) | \
    (((uint8_t)(data) & WORD_08(01000000)) >> 5) | \
    (((uint8_t)(data) & WORD_08(00100000)) >> 3) | \
    (((uint8_t)(data) & WORD_08(00010000)) >> 1) | \
    (((uint8_t)(data) & WORD_08(00001000)) << 1) | \
    (((uint8_t)(data) & WORD_08(00000100)) << 3) | \
    (((uint8_t)(data) & WORD_08(00000010)) << 5) | \
    (((uint8_t)(data) & WORD_08(00000001)) << 7)   \
)

#define SWAP_WORD_16(data) (                                 \
    (((uint16_t)(data) & WORD_16(00000000,11111111)) << 8) | \
    (((uint16_t)(data) & WORD_16(11111111,00000000)) >> 8)   \
)

#define SWAP_WORD_32(data) (                                                    \
    (((uint32_t)(data) & WORD_32(00000000,00000000,00000000,11111111)) << 24) | \
    (((uint32_t)(data) & WORD_32(00000000,00000000,11111111,00000000)) <<  8) | \
    (((uint32_t)(data) & WORD_32(00000000,11111111,00000000,00000000)) >>  8) | \
    (((uint32_t)(data) & WORD_32(11111111,00000000,00000000,00000000)) >> 24)   \
)
// clang-format on

#define BY_VAL(x) (uint32_t)(x)
#define BY_REF(x) *((uint32_t*)&(x))

#define SET_MASK(mask_bit, mask_pos) (BY_VAL(mask_bit) << BY_VAL(mask_pos))
#define NOT_MASK(mask_bit, mask_pos) (~SET_MASK(mask_bit, mask_pos))

#define SHL_BITS(val, mask_bit, mask_pos) ((BY_VAL(val) & BY_VAL(mask_bit)) << BY_VAL(mask_pos))
#define SHR_BITS(val, mask_bit, mask_pos) ((BY_VAL(val) >> BY_VAL(mask_pos)) & BY_VAL(mask_bit))

#define SET_BITS(dst, mask_bit, mask_pos) BY_REF(dst) = (BY_REF(dst) | SET_MASK(mask_bit, mask_pos))
#define CLS_BITS(dst, mask_bit, mask_pos) BY_REF(dst) = (BY_REF(dst) & NOT_MASK(mask_bit, mask_pos))

#define READ_BITS(src, mask_bit, mask_pos) SHR_BITS(src, mask_bit, mask_pos)
#define WRITE_BITS(dst, mask_bit, mask_pos, val) \
    CLS_BITS(dst, mask_bit, mask_pos) | SHL_BITS(val, mask_bit, mask_pos)

// MEMORY/BUFFER macros
#define GB_ARRAY_32(x) ((uint32_t*)&(x))

#define GB_COPY_08(d, s, n)                                                     \
    {                                                                           \
        for (size_t i = 0; i < n; ++i) ((uint8_t*)(d))[i] = ((uint8_t*)(s))[i]; \
    }

#define GB_COPY_16(d, s, n)                                                       \
    {                                                                             \
        for (size_t i = 0; i < n; ++i) ((uint16_t*)(d))[i] = ((uint16_t*)(s))[i]; \
    }

#define GB_COPY_32(d, s, n)                                                       \
    {                                                                             \
        for (size_t i = 0; i < n; ++i) ((uint32_t*)(d))[i] = ((uint32_t*)(s))[i]; \
    }

#define GB_SET_08(x, s)                                                  \
    {                                                                    \
        const size_t N = sizeof(x);                                      \
        for (size_t i = 0; i < N; ++i) ((uint8_t*)&(x))[i] = (uint8_t)s; \
    }

#define GB_SET_16(x, s)                                                    \
    {                                                                      \
        const size_t N = sizeof(x) / 2;                                    \
        for (size_t i = 0; i < N; ++i) ((uint16_t*)&(x))[i] = (uint16_t)s; \
    }

#define GB_SET_32(x, s)                                                    \
    {                                                                      \
        const size_t N = sizeof(x) / 4;                                    \
        for (size_t i = 0; i < N; ++i) ((uint32_t*)&(x))[i] = (uint32_t)s; \
    }

#define GB_ZEROS_08(x)                                          \
    {                                                           \
        const size_t N = sizeof(x);                             \
        for (size_t i = 0; i < N; ++i) ((uint8_t*)&(x))[i] = 0; \
    }

#define GB_ZEROS_16(x)                                           \
    {                                                            \
        const size_t N = sizeof(x) / 2;                          \
        for (size_t i = 0; i < N; ++i) ((uint16_t*)&(x))[i] = 0; \
    }

#define GB_ZEROS_32(x)                                           \
    {                                                            \
        const size_t N = sizeof(x) / 4;                          \
        for (size_t i = 0; i < N; ++i) ((uint32_t*)&(x))[i] = 0; \
    }

// MATH macros
#define GB_MOD_INC(x, y) ((x) = ((x) + 1) % (y))

// *****************************************************************************
// *****************************************************************************
// SEGMENT Functions
// *****************************************************************************
// *****************************************************************************

void gb_memcpy(void* dst, void* src, size_t len);

void gb_memset(void* dst, char val, size_t len);

void gb_zeros(void* dst, size_t len);

#endif // GB_UTILS_H

/* *****************************************************************************
 End of File
 */
