#!/bin/sh
./cleanup.sh
# random the visit num of each object
objNum=10240
g++ my_rand_machine.cpp -lm -o my_rand_machine
# $objNum random visit [0 - $objNum-1]
./my_rand_machine $objNum 0 $objNum-1 hotspot.csv
#./my_rand_machine 1024 50 100 hotspot.txt

# normal distribution of visiting objects
g++ my_normal_distribution.cpp -lm -o my_normal_distribution
# 120s,min = 0, max = 99s, miu = (max + min)/2
./my_normal_distribution 120 0 99 normal_distribution.csv
if [ ! -f "normal_distribution.csv" ]
then
	echo "normal_distribution.csv no exist \n"	
	exit 0;
fi
#for line in $(cat hotspot.txt)
#do
#	echo "File:${line}"
#done;

## create the crush map file, (name bucktype size),size is the num of its leafnode, and root must set 0 to ensure only one root bucket
rm tmp.map
#crushtool --build --num_osds 16 host straw 2 rack straw 2 cabinet straw 2 root straw 0 -o tmp.map
crushtool --build --num_osds 128 host straw 8 rack straw 4 cabinet straw 2 root straw 0 -o tmp.map
if [ ! -f "tmp.map" ]
then
	echo "crush map no exist! \n"
	exit 0;
fi
#decompile the map 
crushtool -d tmp.map -o decompile-crushmap
#compile the map : crushtool -c tmp.map -o compile-crushmap

# output the current osd tree
osdmaptool --createsimple 128 tmp.osdmap --clobber
osdmaptool tmp.osdmap --import-crush tmp.map
osdmaptool tmp.osdmap --tree > osdtree

## output the placement information to the data-placement-information.csv, set the replica num is 3 , obj from 0 to 10240
crushtool -i tmp.map --test --num-rep 3 --min_x 0 --max_x 10240 --output-csv
if [ ! -f "data-placement_information.csv" ]
then
	echo "data csv no exist!"
	exit 0;
fi
## parse the file
#for osdline in $(cat data-placement_information.csv)
#do
#	echo "${osdline}" | gawk -F "," '{print $2}'
#	#gawk -F "," '{print $2}' ${osdline}
#done;

g++ my_parse.cpp -o my_parse -g
./my_parse 128

