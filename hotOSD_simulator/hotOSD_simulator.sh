#!/bin/sh
# random the visit num of each object
objNum=10240
g++ my_rand_machine.cpp -lm -o my_rand_machine
#random $objNum range from [50,100000]
./my_rand_machine $objNum 50 1000000 hotspot.txt
#./my_rand_machine 1024 50 100 hotspot.txt

#for line in $(cat hotspot.txt)
#do
#	echo "File:${line}"
#done;

## create the crush map file, (name bucktype size),size is the num of its leafnode, and root must set 0 to ensure only one root bucket
rm tmp.map
#crushtool --build --num_osds 16 host straw 2 rack straw 2 cabinet straw 2 root straw 0 -o tmp.map
crushtool --build --num_osds 128 host straw 8 rack straw 4 cabinet straw 2 root straw 0 -o tmp.map

#decompile the map : crushtool -d tmp.map -o tmp.map
#compile the map : crushtool -c tmp.map -o tmp.map

## output the placement information to the data-placement-information.csv, set the replica num is 3 , obj from 0 to 10240
rm *.csv
crushtool -i tmp.map --test --num-rep 3 --min_x 0 --max_x 10240 --output-csv

## parse the file
#for osdline in $(cat data-placement_information.csv)
#do
#	echo "${osdline}" | gawk -F "," '{print $2}'
#	#gawk -F "," '{print $2}' ${osdline}
#done;

rm hotOSD.result;
g++ my_parse.cpp -o my_parse -g
./my_parse 128

