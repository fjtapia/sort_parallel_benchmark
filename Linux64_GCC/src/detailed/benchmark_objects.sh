clear
echo "=================================================================="
echo "==              B E N C H M A R K   O B J E C T S               =="
echo "==                                                              =="
echo "==                 G C C      C O M P I L E R                   =="
echo "==                                                              =="
echo "==          B O O S T :: S O R T :: P A R A L L E L             =="
echo "==                                                              =="
echo "==                  A L G O R I T H M S                         =="
echo "==                                                              =="
echo "=================================================================="
echo "."
date
echo "C O M P I L I N G . . . . . . . . . . ."
echo "."
g++ ./file_generator.cpp -std=c++11 -march=native -w -fexceptions -O3 -I../../../include    -s  -o file_generator
g++ ./parallel_objects.cpp -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../../include   -pthread  -s  -lpthread -ltbb  -o parallel_objects
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 20 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "The results will be stored in the file Results_Objects.txt"
echo "."
echo " please, be patient .........."
echo "."
echo "==================================================================" > Results_Objects.txt 2>&1
echo "                B E N C H M A R K   N U M B E R S                 " >> Results_Objects.txt 2>&1
echo "." >> Results_Objects.txt 2>&1
lscpu >> Results_Objects.txt 2>&1
echo "==================================================================" >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 1 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 2 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 3 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 4 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 5 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 6 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 7 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 8 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 9 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 10 >> Results_Objects.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_objects 11 >> Results_Objects.txt 2>&1

rm input.bin
rm file_generator
rm parallel_objects
echo "."
date
echo "."
echo "E N D"
echo "."
