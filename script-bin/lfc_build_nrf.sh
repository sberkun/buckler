#!/usr/bin/env bash

SCRIPT_DIR=$(realpath $(dirname "${BASH_SOURCE[0]}"))
TARGET_DIR=src-gen/$(basename $1 .lf)

echo "attempting to run lfc -n $1"
lfc -n $1

echo "starting NRF generation script into $TARGET_DIR"
echo "pwd is $(pwd)"

cp $SCRIPT_DIR/../script/lf_nRF52832_support.c $TARGET_DIR/core/platform/
cp $SCRIPT_DIR/../script/lf_nRF52832_support.h $TARGET_DIR/core/platform/
cp $SCRIPT_DIR/../script/platform.h $TARGET_DIR/core/
cp $SCRIPT_DIR/../script/include_nrf.c $TARGET_DIR/

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
' $(realpath $SCRIPT_DIR/..) $(realpath $SCRIPT_DIR/..) > $TARGET_DIR/Makefile

echo "NRF generation completed successfully"


read -p "cd and run make flash? y/n: " yn
case $yn in
  [Yy]* ) cd $TARGET_DIR; make flash; exit;;
  * ) exit;;
esac

