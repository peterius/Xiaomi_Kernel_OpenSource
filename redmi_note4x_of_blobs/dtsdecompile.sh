#!/bin/bash

#find ./ -name "*.dtb" -exec \
#"dtc -I dtb -O dts {} > `sed -e 's/\.dtb/\/.dts/' {}`"

for file in *.dtb
do
	outfile="${file/\.dtb/\.dts}"
	dtc -I dtb -O dts ${file} > $outfile
done
