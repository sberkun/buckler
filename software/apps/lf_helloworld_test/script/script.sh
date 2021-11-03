#!/bin/bash


# takes arguments ($1 = lf compiler) and ($2 = lf file)

PROJNAME=$(basename $2 .lf)
echo "Project name is:" $PROJNAME
# $1 $2
rm -rf $(pwd)/$PROJNAME
rm -f $(pwd)/main.c
cp -r $(dirname $2)/src-gen/$PROJNAME $(pwd)/$PROJNAME
cp $(pwd)/script/lf_nRF52832_support.c $(pwd)/$PROJNAME/core/platform/
cp $(pwd)/script/lf_nRF52832_support.h $(pwd)/$PROJNAME/core/platform/
cp $(pwd)/script/platform.h $(pwd)/$PROJNAME/core/

printf '
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
' > $(pwd)/main.c
printf "#include \"$PROJNAME/$PROJNAME.c\"
#include \"$PROJNAME/core/platform/lf_nRF52832_support.c\"" >> $(pwd)/main.c

