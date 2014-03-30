#!/bin/bash
if [ $# -eq 0 ]; then
	echo "Usage: $0 <path to xml where to generate>"
	exit
fi
file=$1
array=( $(aticonfig --adapter=all --od-gettemperature | grep Temperature | rev | cut -c 3-7 | rev) )
index=1
element="temperatures"
item="card"
unit="°C"

echo -e "<$element unit=\"$unit\">" >> $file
for load in ${array[@]}
do
	echo -e "\t<$item id=\"$index\">$load</$item>" >> $file
	let "index++"
done

echo -e "</$element>" >> $file
