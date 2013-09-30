#!/bin/sh
g++ my_rand_machine.cpp -lm -o my_rand_machine
./my_rand_machine 1024 50 100 hotspot.txt
#for line in $(cat hotspot.txt)
#do
#	echo "File:${line}"
#done;

## create the crush map file
rm tmp.map
crushtool --build --num_osds 16 host straw 2 rack straw 2 cabinet straw 2 root straw 0 -o tmp.map
#crushtool -d tmp.map -o tmp.map
#crushtool -c tmp.map -o tmp.map

## output the placement information to the data-placement-information.csv
rm *.csv
crushtool -i tmp.map --test --num-rep 3 --output-csv

## parse the file
#for osdline in $(cat data-placement_information.csv)
#do
#	echo "${osdline}" | gawk -F "," '{print $2}'
#	#gawk -F "," '{print $2}' ${osdline}
#done;

rm hotOSD.result;
g++ my_parse.cpp -o my_parse -g
./my_parse

