/// ============================================================================
/// File    : GFFT.hpp
/// Version : 0.1
/// Date    : May 2021
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GFFT_HPP
#define GFFT_HPP

#include <cmath> // round
#include <fftw3.h>
#include <type_traits> // is_same_v, is_floating_point_v

namespace gFFT {
    // NOTE: DIR choice
    struct FORWARD {
        bool _;
    };
    struct BACKWARD {
        bool _;
    };
    // NOTE: OP choice
    struct NORMAL {
        bool _;
    };
    struct SCALED {
        bool _;
    };
    struct SHIFTED {
        bool _;
    };
    struct SCALED_AND_SHIFTED {
        bool _;
    };
} // namespace gFFT

template <typename DIR, size_t NUM> class GFFT {
    public:
    GFFT() {
        if constexpr (std::is_same_v<DIR, gFFT::FORWARD>) {
            m_plan = fftw_plan_dft_1d(NUM, m_signal, m_middle, FFTW_FORWARD, FFTW_ESTIMATE);
        }
        if constexpr (std::is_same_v<DIR, gFFT::BACKWARD>) {
            m_plan = fftw_plan_dft_1d(NUM, m_signal, m_middle, FFTW_BACKWARD, FFTW_ESTIMATE);
        }
    }

    ~GFFT() {
        fftw_destroy_plan(m_plan);
    }

    template <typename T> bool SetSignal(T *signal_buffer, size_t signal_length) {
        if (signal_length == 2 * NUM) {
            for (size_t i{0}; i < NUM; ++i) {
                m_signal[i][0] = signal_buffer[2 * i + 0];
                m_signal[i][1] = signal_buffer[2 * i + 1];
            }
            return true;
        }
        return false;
    }

    template <typename OP> void Execute() {
        fftw_execute(m_plan);

        if constexpr (std::is_same_v<OP, gFFT::NORMAL>) {
            for (size_t i{0}; i < NUM; ++i) {
                m_result[i][0] = m_middle[i][0];
                m_result[i][1] = m_middle[i][1];
            }
        }

        if constexpr (std::is_same_v<OP, gFFT::SCALED>) {
            for (size_t i{0}; i < NUM; ++i) {
                m_result[i][0] = m_middle[i][0] / NUM;
                m_result[i][1] = m_middle[i][1] / NUM;
            }
        }

        if constexpr (std::is_same_v<OP, gFFT::SHIFTED>) {
            auto K{NUM / 2};
            if constexpr ((NUM & 1) == 0) {
                for (size_t i{0}; i < K; ++i) {
                    m_result[K + i][0] = m_middle[i][0];
                    m_result[K + i][1] = m_middle[i][1];
                }
                for (size_t i{0}; i < K; ++i) {
                    m_result[i][0] = m_middle[K + i][0];
                    m_result[i][1] = m_middle[K + i][1];
                }
            }
            else {
                for (size_t i{0}; i <= K; ++i) {
                    m_result[K + i][0] = m_middle[i][0];
                    m_result[K + i][1] = m_middle[i][1];
                }
                for (size_t i{0}; i < K; ++i) {
                    m_result[i][0] = m_middle[K + 1 + i][0];
                    m_result[i][1] = m_middle[K + 1 + i][1];
                }
            }
        }

        if constexpr (std::is_same_v<OP, gFFT::SCALED_AND_SHIFTED>) {
            auto K{NUM / 2};
            if constexpr ((NUM & 1) == 0) {
                for (size_t i{0}; i < K; ++i) {
                    m_result[K + i][0] = m_middle[i][0] / NUM;
                    m_result[K + i][1] = m_middle[i][1] / NUM;
                }
                for (size_t i{0}; i < K; ++i) {
                    m_result[i][0] = m_middle[K + i][0] / NUM;
                    m_result[i][1] = m_middle[K + i][1] / NUM;
                }
            }
            else {
                for (size_t i{0}; i <= K; ++i) {
                    m_result[K + i][0] = m_middle[i][0] / NUM;
                    m_result[K + i][1] = m_middle[i][1] / NUM;
                }
                for (size_t i{0}; i < K; ++i) {
                    m_result[i][0] = m_middle[K + 1 + i][0] / NUM;
                    m_result[i][1] = m_middle[K + 1 + i][1] / NUM;
                }
            }
        }
    }

    template <typename T> bool GetResult(T *result_buffer, size_t result_length) {
        if (result_length == 2 * NUM) {
            for (size_t i{0}; i < NUM; ++i) {
                if constexpr (std::is_floating_point_v<T>) {
                    result_buffer[2 * i + 0] = m_result[i][0];
                    result_buffer[2 * i + 1] = m_result[i][1];
                }
                else {
                    result_buffer[2 * i + 0] = std::round(m_result[i][0]);
                    result_buffer[2 * i + 1] = std::round(m_result[i][1]);
                }
            }
            return true;
        }
        return false;
    }

    auto signal() {
        return m_signal;
    }

    auto result() {
        return m_result;
    }

    auto length() {
        return NUM;
    }

    private:
    fftw_plan    m_plan{nullptr};
    fftw_complex m_signal[NUM];
    fftw_complex m_middle[NUM];
    fftw_complex m_result[NUM];
};

#endif // GFFT_HPP