/* MacOS API support for the C target of Lingua Franca. */

/*************
Copyright (c) 2021, The University of California at Berkeley.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************/

/** Linux API support for the C target of Lingua Franca.
 *  
 *  @author{Soroush Bateni <soroush@utdallas.edu>}
 */

#include "lf_nRF52832_support.h"
#include "../platform.h"

#include "nrf_delay.h"
#include "nrf.h"
#include "nrf_mtx.h"

#ifdef NUMBER_OF_WORKERS
#if __STDC_VERSION__ < 201112L || defined (__STDC_NO_THREADS__) // (Not C++11 or later) or no threads support

/**
 * Create a new thread, starting with execution of lf_thread getting passed
 * arguments. The new handle is stored in thread.
 *
 * @return 0 on success, error number otherwise (see pthread_create()).
 */
int lf_thread_create(_lf_thread_t* thread, void *(*lf_thread) (void *), void* arguments) {
    //TODO: implement
    return 0;
}

/**
 * Make calling thread wait for termination of the thread.  The
 * exit status of the thread is stored in thread_return, if thread_return
 * is not NULL.
 *
 * @return 0 on success, error number otherwise (see pthread_join()).
 */
int lf_thread_join(_lf_thread_t thread, void** thread_return) {
    //TODO: implement
    return 0;
}

/**
 * Initialize a mutex.
 *
 * @return 0 on success, error number otherwise (see pthread_mutex_init()).
 */
int lf_mutex_init(_lf_mutex_t* mutex) {
    //TODO: implement
    return 0;
}

/**
 * Lock a mutex.
 *
 * @return 0 on success, error number otherwise (see pthread_mutex_lock()).
 */
int lf_mutex_lock(_lf_mutex_t* mutex) {
    //TODO: implement
    return 0;
}

/** 
 * Unlock a mutex.
 *
 * @return 0 on success, error number otherwise (see pthread_mutex_unlock()).
 */
int lf_mutex_unlock(_lf_mutex_t* mutex) {
    //TODO: implement
    return 0;
}

/** 
 * Initialize a conditional variable.
 *
 * @return 0 on success, error number otherwise (see pthread_cond_init()).
 */
int lf_cond_init(_lf_cond_t* cond) {
    //TODO: implement
    return 0;
}

/** 
 * Wake up all threads waiting for condition variable cond.
 *
 * @return 0 on success, error number otherwise (see pthread_cond_broadcast()).
 */
int lf_cond_broadcast(_lf_cond_t* cond) {
    //TODO: implement
    return 0;
}

/** 
 * Wake up one thread waiting for condition variable cond.
 *
 * @return 0 on success, error number otherwise (see pthread_cond_signal()).
 */
int lf_cond_signal(_lf_cond_t* cond) {
    //TODO: implement
    return 0;
}

/** 
 * Wait for condition variable "cond" to be signaled or broadcast.
 * "mutex" is assumed to be locked before.
 *
 * @return 0 on success, error number otherwise (see pthread_cond_wait()).
 */
int lf_cond_wait(_lf_cond_t* cond, _lf_mutex_t* mutex) {
    //TODO: implement
    return 0;
}

/** 
 * Block current thread on the condition variable until condition variable
 * pointed by "cond" is signaled or time pointed by "absolute_time_ns" in
 * nanoseconds is reached.
 * 
 * @return 0 on success, LF_TIMEOUT on timeout, and platform-specific error
 *  number otherwise (see pthread_cond_timedwait).
 */
int lf_cond_timedwait(_lf_cond_t* cond, _lf_mutex_t* mutex, int64_t absolute_time_ns) {
    //TODO: implement
    return 0;
}

#else
#include "lf_C11_threads_support.c"
#endif
#endif


/**
 * Offset to _LF_CLOCK that would convert it
 * to epoch time.
 * For CLOCK_REALTIME, this offset is always zero.
 * For CLOCK_MONOTONIC, it is the difference between those
 * clocks at the start of the execution.
 */
interval_t _lf_epoch_offset = 0LL;

/**
 * Convert a _lf_time_spec_t ('tp') to an instant_t representation in
 * nanoseconds.
 *
 * @return nanoseconds (long long).
 */
instant_t convert_timespec_to_ns(struct timespec tp) {
    return tp.tv_sec * 1000000000 + tp.tv_nsec;
}

/**
 * Convert an instant_t ('t') representation in nanoseconds to a
 * _lf_time_spec_t.
 *
 * @return _lf_time_spec_t representation of 't'.
 */
struct timespec convert_ns_to_timespec(instant_t t) {
    struct timespec tp;
    tp.tv_sec = t / 1000000000;
    tp.tv_nsec = (t % 1000000000);
    return tp;
}

/**
 * Calculate the necessary offset to bring _LF_CLOCK in parity with the epoch
 * time reported by CLOCK_REALTIME.
 */
void calculate_epoch_offset() {
    // unimplemented - on the nrf, probably not possible to get a bearing on real time
}

/**
 * Initialize the LF clock.
 */
void lf_initialize_clock() {
    // Initialize TIMER4 as a free running timer
    // 1) Set to be a 32 bit timer
    // 2) Set to count at 1MHz
    // 3) Clear the timer
    // 4) Start the timer
    NRF_TIMER4->BITMODE = 3;
    NRF_TIMER4->PRESCALER = 4;
    NRF_TIMER4->TASKS_CLEAR = 1;
    NRF_TIMER4->TASKS_START = 1;
}

/**
 * Fetch the value of _LF_CLOCK (see lf_linux_support.h) and store it in tp. The
 * timestamp value in 't' will always be epoch time, which is the number of
 * nanoseconds since January 1st, 1970.
 *
 * @return 0 for success, or -1 for failure. In case of failure, errno will be
 *  set appropriately (see `man 2 clock_gettime`).
 */
int lf_clock_gettime(instant_t* t) {
    if (t == NULL) {
        // The t argument address references invalid memory
        // errno = EFAULT; //TODO: why does this not work with new build process?
        return -1;
    }

    NRF_TIMER4->TASKS_CAPTURE[1] = 1;
    instant_t tp_in_us = (instant_t)(NRF_TIMER4->CC[1]);

    *t = tp_in_us * 1000 + _lf_epoch_offset;
    return 0;
}




/**
 * Pause execution for a number of nanoseconds.
 *
 * A Linux-specific clock_nanosleep is used underneath that is supposedly more
 * accurate.
 *
 * @return 0 for success, or -1 for failure. In case of failure, errno will be
 *  set appropriately (see `man 2 clock_nanosleep`).
 */
int lf_nanosleep(instant_t requested_time) {
    instant_t requested_ms = requested_time / 1000000;
    nrf_delay_ms((int) requested_ms);
    return 0;
}