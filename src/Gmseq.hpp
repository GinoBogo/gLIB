/// ============================================================================
/// File    : Gmseq.hpp
/// Version : 0.1
/// Date    : May 2021
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GMSEQ_HPP
#define GMSEQ_HPP

#include <cmath> // log2
#include <vector>

template <typename T, size_t L> class Gmseq {

    public:
    Gmseq() {
        m_degree = L;
        Reset();
    };

    void Reset() {
        for (decltype(L) i = 0; i < m_degree; ++i) {
            m_regs[i] = 1;
            m_taps[i] = 0;
        }

        std::vector<T> poly;

        switch (m_degree) {
            case 2:
                poly.assign({1, 2});
                break;
            case 3:
                poly.assign({1, 3});
                break;
            case 4:
                poly.assign({1, 4});
                break;
            case 5:
                poly.assign({2, 5});
                break;
            case 6:
                poly.assign({1, 6});
                break;
            case 7:
                poly.assign({1, 7});
                break;
            case 8:
                poly.assign({1, 2, 7, 8});
                break;
            case 9:
                poly.assign({4, 9});
                break;
            case 10:
                poly.assign({3, 10});
                break;
            case 11:
                poly.assign({9, 11});
                break;
            case 12:
                poly.assign({6, 8, 11, 12});
                break;
            case 13:
                poly.assign({9, 10, 12, 13});
                break;
            case 14:
                poly.assign({4, 8, 13, 14});
                break;
            case 15:
                poly.assign({14, 15});
                break;
            case 16:
                poly.assign({4, 13, 15, 16});
                break;
            case 17:
                poly.assign({14, 17});
                break;
            case 18:
                poly.assign({11, 18});
                break;
            case 19:
                poly.assign({14, 17, 18, 19});
                break;
            case 20:
                poly.assign({17, 20});
                break;
            case 21:
                poly.assign({19, 21});
                break;
            case 22:
                poly.assign({21, 22});
                break;
            case 23:
                poly.assign({18, 23});
                break;
            case 24:
                poly.assign({17, 22, 23, 24});
                break;
            case 25:
                poly.assign({22, 25});
                break;
            case 26:
                poly.assign({20, 24, 25, 26});
                break;
            case 27:
                poly.assign({22, 25, 26, 27});
                break;
            case 28:
                poly.assign({25, 28});
                break;
            case 29:
                poly.assign({27, 29});
                break;
            case 30:
                poly.assign({7, 28, 29, 30});
                break;
            default:
                break;
        }

        for (auto p : poly) {
            m_taps[p - 1] = 1;
        }
    }

    // INFO: MATLAB -> mseq(2, 8, 0)
    T Update() {
        T feed = 0;

        for (decltype(L) i = 0; i <= m_degree - 1; ++i) {
            if (m_taps[i]) {
                feed ^= m_regs[i];
            }
        }

        for (decltype(L) i = m_degree - 1; i > 0; --i) {
            m_regs[i] = m_regs[i - 1];
        }
        m_regs[0] = feed;

        return feed;
    }

    private:
    size_t m_degree;
    T      m_regs[L];
    T      m_taps[L];
};

#endif // GMSEQ_HPP