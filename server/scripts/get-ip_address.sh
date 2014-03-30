#!/bin/bash
if [ $# -eq 0 ]; then
	echo "Usage: $0 <path to xml where to generate> <ethernet device>"
	exit
fi
file=$1
device=$2
ip=$(ifconfig $device | grep -e 'inet ad' | cut -d " " -f 12 | cut -c 5-)
index=1
element="ip-address"

echo -e "<$element device=\"$device\">$ip</$element>" >> $file
