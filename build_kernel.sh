#!/bin/bash

export LFMROOT=`readlink -f ../`
export ARCH=arm64
export CROSS_COMPILE=$LFMROOT/toolchain/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
export KBUILD_VERBOSE=1
#make mido-perf_defconfig
make mido_nomodules_console_defconfig

make -j4
make dtbs
#make -j4 modules

#make -j4 dtbs_install

# dtb files aren't compiling? so
./with_dtb.sh redmi_note4x_of_blobs
