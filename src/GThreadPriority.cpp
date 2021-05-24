////////////////////////////////////////////////////////////////////////////////
/// \file      GThreadPriority.cpp
/// \version   0.1
/// \date      December 2020
/// \author    Gino Francesco Bogo
/// \copyright This file is released under the MIT license
////////////////////////////////////////////////////////////////////////////////

#include "GThreadPriority.hpp"

#include <sched.h>

namespace GThreadPriority {

    int get_priority() {
        int         pol;
        sched_param param;
        pthread_getschedparam(pthread_self(), &pol, &param);
        return param.sched_priority;
    }

    int get_priority(std::thread &thread) {
        int         pol;
        sched_param param;
        pthread_getschedparam(thread.native_handle(), &pol, &param);
        return param.sched_priority;
    }

    void get_priority_range(int *min_priority, int *max_priority) {
        int         pol;
        sched_param param;
        pthread_getschedparam(pthread_self(), &pol, &param);
        *min_priority = sched_get_priority_min(pol);
        *max_priority = sched_get_priority_max(pol);
    }

    void get_priority_range(std::thread &thread, int *min_priority, int *max_priority) {
        int         pol;
        sched_param param;
        pthread_getschedparam(thread.native_handle(), &pol, &param);
        *min_priority = sched_get_priority_min(pol);
        *max_priority = sched_get_priority_max(pol);
    }

    bool set_priority(int priority) {
        int         pol;
        sched_param param;
        pthread_getschedparam(pthread_self(), &pol, &param);
        param.sched_priority = priority;
        return 0 == pthread_setschedparam(pthread_self(), pol, &param);
    }

    bool set_priority(std::thread &thread, int priority) {
        int         pol;
        sched_param param;
        pthread_getschedparam(thread.native_handle(), &pol, &param);
        param.sched_priority = priority;
        return 0 == pthread_setschedparam(thread.native_handle(), pol, &param);
    }

} // namespace GThreadPriority
