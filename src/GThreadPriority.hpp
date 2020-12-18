/// ============================================================================
/// File    : GThreadPriority.hpp
/// Version : 0.1
/// Date    : December 2020
/// Author  : Gino Francesco Bogo
/// License : MIT
/// ============================================================================

#ifndef GTHREADPRIORITY_HPP

#include <thread>

int GetThreadPriority();

int GetThreadPriority(std::thread &thread);

void GetThreadPriorityRange(int *min_priority, int *max_priority);

void GetThreadPriorityRange(std::thread &thread, int *min_priority, int *max_priority);

bool SetThreadPriority(int priority);

bool SetThreadPriority(std::thread &thread, int priority);

#endif // GTHREADPRIORITY_HPP