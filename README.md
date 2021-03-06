hotspot_simulator
=================

the hotspot simulator to monitor the OSD cluster's performance.
the crushtool and osdmaptool must be installed first of all.

crushtool and osdmaptool can be found in /usr/bin/, /usr/sbin/, or /usr/local/bin, /usr/local/sbin .

the hotspot_simulator contains three parts:

1. random number generator -- my_rand_machine.cpp, my_rand_machine1.cpp, my_gaussrand.cpp

   that outputs the file hotspot.txt as the simulator of large amount visit on each object.
   my_rand_machine1 is other way to produce random number.
   my_gaussrand is the gauss method to produce random numbers.
   
2. parser -- my_parse.cpp

   parse the file hotspot.txt and the data-placement-information.csv, then calculates the OSD's PV, 
   output to the file hotOSD.csv, the object PV output to the file visitObject.csv , 
   and the crushmap(decompile), osdtree of current crushmap, and timePeriod.csv.

3. main simulator -- hotOSD_simulator.sh

   that calls the random number generator, and use crushtool to build a map file tmp.map, then placement objects.
   finally calls the parser to output the result file -- hotOSD.csv, and the object PV result is in file -- visitObject.csv.

4. normal distribution -- my_normal_distribution.cpp

   produce the normal distribution of the probability to visit files : normal_distribution.csv

More info:

0. crushmap: http://ceph.com/docs/master/rados/operations/crush-map/

1. crushmaptool: http://ceph.com/docs/next/man/8/crushtool/

2. osdmaptool: http://ceph.com/docs/next/man/8/osdmaptool/
