/// ============================================================================
/// File    : GThreadPriority.cpp
/// Version : 0.1
/// Date    : December 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#include "GThreadPriority.hpp"

#include <sched.h>

int GetThreadPriority() {
    int         pol;
    sched_param param;
    pthread_getschedparam(pthread_self(), &pol, &param);
    return param.sched_priority;
}

int GetThreadPriority(std::thread &thread) {
    int         pol;
    sched_param param;
    pthread_getschedparam(thread.native_handle(), &pol, &param);
    return param.sched_priority;
}

void GetThreadPriorityRange(int *min_priority, int *max_priority) {
    int         pol;
    sched_param param;
    pthread_getschedparam(pthread_self(), &pol, &param);
    *min_priority = sched_get_priority_min(pol);
    *max_priority = sched_get_priority_max(pol);
}

void GetThreadPriorityRange(std::thread &thread, int *min_priority, int *max_priority) {
    int         pol;
    sched_param param;
    pthread_getschedparam(thread.native_handle(), &pol, &param);
    *min_priority = sched_get_priority_min(pol);
    *max_priority = sched_get_priority_max(pol);
}

bool SetThreadPriority(int priority) {
    int         pol;
    sched_param param;
    pthread_getschedparam(pthread_self(), &pol, &param);
    param.sched_priority = priority;
    return 0 == pthread_setschedparam(pthread_self(), pol, &param);
}

bool SetThreadPriority(std::thread &thread, int priority) {
    int         pol;
    sched_param param;
    pthread_getschedparam(thread.native_handle(), &pol, &param);
    param.sched_priority = priority;
    return 0 == pthread_setschedparam(thread.native_handle(), pol, &param);
}
