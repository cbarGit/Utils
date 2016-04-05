#! /bin/bash

IFS='
'
#for debug
#echo $1

new=`basename $1 | sed -e 's/ /_/g'`
mv $1 $new

#for debug
#echo $new

for ((n=1;n<8;n++)); do 
	dd if=/dev/urandom of=$new bs=21 count=1 conv=notrunc 
done 
rm $new
echo -n "File $new wiped."


