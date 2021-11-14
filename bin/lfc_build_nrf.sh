#!/usr/bin/env bash

SCRIPT_DIR=$(realpath $(dirname "${BASH_SOURCE[0]}"))

echo "starting NRF generation script for $1"
echo "pwd is $(pwd)"

cp $SCRIPT_DIR/../script/lf_nRF52832_support.c ../src-gen/$1/core/platform/
cp $SCRIPT_DIR/../script/lf_nRF52832_support.h ../src-gen/$1/core/platform/
cp $SCRIPT_DIR/../script/platform.h ../src-gen/$1/core/
cp $SCRIPT_DIR/../script/include_nrf.c ../src-gen/$1/

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
' $(realpath $SCRIPT_DIR/..) $(realpath $SCRIPT_DIR/..) > ../src-gen/$1/Makefile

echo "NRF generation script completed successfully"