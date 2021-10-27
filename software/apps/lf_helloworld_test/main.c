// Blink app
//
// Blinks the LEDs on Buckler

//#include <stdbool.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <time.h>

//#include "app_error.h"
//#include "nrf.h"
//#include "nrf_delay.h"
//#include "nrfx_gpiote.h"
//#include "nrf_gpio.h"
//#include "nrf_log.h"
//#include "nrf_log_ctrl.h"
//#include "nrf_log_default_backends.h"
//#include "nrf_pwr_mgmt.h"
//#include "nrf_serial.h"

//#include "buckler.h"

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

#include "HelloWorld/HelloWorld.c"
#include "HelloWorld/core/platform/lf_linux_support.c"

