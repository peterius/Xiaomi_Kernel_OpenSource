#!/bin/sh

for file in $1/*.dts
do
	outfile="${file/\.dts/\.dtb}"
	dtc -O dtb -o $outfile $file
	#-b 0??
done

#cat arch/arm64/boot/Image.gz arch/arm/boot/dts/qcom/*.dtb > ../Image.dtb
cat arch/arm64/boot/Image.gz $1/*.dtb > ../Imagedtb
