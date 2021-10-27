#include <time.h>
#include <errno.h>

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
    /*
    if (_LF_CLOCK == CLOCK_REALTIME) {
        // Set the epoch offset to zero (see tag.h)
        _lf_epoch_offset = 0LL;
    } else {
        // Initialize _lf_epoch_offset to the difference between what is
        // reported by whatever clock LF is using (e.g. CLOCK_MONOTONIC) and
        // what is reported by CLOCK_REALTIME.
        struct timespec physical_clock_snapshot, real_time_start;

        clock_gettime(_LF_CLOCK, &physical_clock_snapshot);
        long long physical_clock_snapshot_ns = convert_timespec_to_ns(physical_clock_snapshot);


        clock_gettime(CLOCK_REALTIME, &real_time_start);
        long long real_time_start_ns = convert_timespec_to_ns(real_time_start);

        _lf_epoch_offset = real_time_start_ns - physical_clock_snapshot_ns;
    }
    */
}

/**
 * Initialize the LF clock.
 */
void lf_initialize_clock() {
    calculate_epoch_offset();
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
        errno = EFAULT;
        return -1;
    }

    NRF_TIMER4->TASKS_CAPTURE[1] = 1;
    instant_t tp_in_us = (instant_t)(NRF_TIMER4->CC[1]);

    *t = tp_in_us * 1000;
    return 0;
}