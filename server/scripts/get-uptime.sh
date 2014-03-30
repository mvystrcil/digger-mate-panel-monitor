#!/bin/bash
if [ $# -eq 0 ]; then
	echo "Usage: $0 <path to xml where to generate>"
	exit
fi
file=$1
uptime=$(uptime | cut -d " " -f 4)
index=1
element="uptime"
item="card"
unit=$(uptime | cut -d " " -f 5 | rev | cut -c 2- | rev)

echo -e "<$element unit=\"$unit\">$uptime</$element>" >> $file
