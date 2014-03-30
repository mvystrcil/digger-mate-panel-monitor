#!/bin/bash
if [ $# -eq 0 ]; then
	echo "Usage: $0 <path to xml where to generate>"
	exit
fi
file=$1
array=( $(aticonfig --adapter=all --od-getclocks | grep load | rev | cut -c 2-3 | rev) )
index=1
element="loads"
item="card"
unit="%"

echo -e "<$element unit=\"$unit\">" >> $file
for load in ${array[@]}
do
	echo -e "\t<$item id=\"$index\">$load</$item>" >> $file
	let "index++"
done

echo -e "</$element>" >> $file
