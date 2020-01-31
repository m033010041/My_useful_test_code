HARDFLOAT_SDK="/usr/local/weintek-i686/sysroots/armv7ahf-vfp-neon-weintek-linux-gnueabi"
MACHINE="G03"
echo ${SDKTARGETSYSROOT}

if [ $MACHINE != "G03" ]; then
	echo "is G03"
else
	echo "is not G03"
fi

if [ ${SDKTARGETSYSROOT} != "$HARDFLOAT_SDK" ]; then
	echo "Please check your environment."
else
	echo "Correct SDK path."
fi
