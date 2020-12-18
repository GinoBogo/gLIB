/// ============================================================================
/// File    : GThreadPriority.hpp
/// Version : 0.1
/// Date    : December 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GTHREADPRIORITY_HPP

#include <thread>

namespace GThreadPriority {

    int get_priority();

    int get_priority(std::thread &thread);

    void get_priority_range(int *min_priority, int *max_priority);

    void get_priority_range(std::thread &thread, int *min_priority, int *max_priority);

    bool set_priority(int priority);

    bool set_priority(std::thread &thread, int priority);

} // namespace GThreadPriority

#endif // GTHREADPRIORITY_HPP