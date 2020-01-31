source /usr/local/weintek-i686/environment-setup-armv7ahf-vfp-neon-weintek-linux-gnueabi
arm-weintek-linux-gnueabi-gcc -march=armv7-a -mfloat-abi=hard -mfpu=neon --sysroot=$SDKTARGETSYSROOT -o route_add route_add.c
