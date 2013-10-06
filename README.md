hotspot_simulator
=================

the hotspot simulator to monitor the OSD cluster's performance.
the crushtool and osdmaptool must be installed first of all.

the hotspot_simulator contains three parts:

1. random number generator -- my_rand_machine, my_rand_machine.cpp 
   that outputs the file hotspot.txt as the simulator of large amount visit on each object.

2. parser -- my_parse, my_parse.cpp
   parse the file hotspot.txt and the data-placement-information.csv, then calculates the OSD's PV, 
   output to the file hotOSD.csv, the object PV output to the file visitObject.csv , 
   and the crushmap(decompile), osdtree of current crushmap.

3. main simulator -- hotOSD_simulator.sh,
   that calls the random number generator, and use crushtool to build a map file tmp.map, then placement objects.
   finally calls the parser to output the result file -- hotOSD.csv, and the object PV result is in file -- visitObject.csv.


More info:
crushmaptool: http://ceph.com/docs/next/man/8/crushtool/
osdmaptool: http://ceph.com/docs/next/man/8/osdmaptool/
