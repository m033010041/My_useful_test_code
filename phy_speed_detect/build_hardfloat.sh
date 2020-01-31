#!/bin/bash
HISTFILE=~/.bash_history
set -o history
source /usr/local/weintek-i686/environment-setup-armv7ahf-vfp-neon-weintek-linux-gnueabi
arm-weintek-linux-gnueabi-gcc -march=armv7-a -mfloat-abi=hard -mfpu=neon --sysroot=$SDKTARGETSYSROOT -o get_phy_speed main.c
