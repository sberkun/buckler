echo "starting NRF generation script for $1"

cp $(dirname $0)/lf_nRF52832_support.c src-gen/$1/core/platform
cp $(dirname $0)/lf_nRF52832_support.h src-gen/$1/core/platform
cp $(dirname $0)/platform.h src-gen/$1/core

printf "
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
#include \"core/platform/lf_nRF52832_support.c\"
" > src-gen/$1/main.c


printf '
# nRF application makefile
PROJECT_NAME = $(shell basename "$(realpath ./)")

# Configurations
NRF_IC = nrf52832
SDK_VERSION = 15
SOFTDEVICE_MODEL = s132

# Source and header files
APP_HEADER_PATHS += .
APP_SOURCE_PATHS += .
APP_SOURCES = $(notdir $(wildcard ./*.c))

# Path to base of nRF52-base repo
NRF_BASE_DIR = %s/nrf52x-base/

# Include board Makefile (if any)
include %s/buckler_revC/Board.mk

# Include main Makefile
include $(NRF_BASE_DIR)make/AppMakefile.mk
' $(realpath $(dirname $0)/../) $(realpath $(dirname $0)/../) > src-gen/$1/Makefile

echo "NRF generation script completed successfully"