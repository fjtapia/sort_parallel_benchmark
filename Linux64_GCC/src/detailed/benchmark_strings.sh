clear
echo "=================================================================="
echo "==             B E N C H M A R K   S T R I N G S                =="
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
g++ ./parallel_strings.cpp      -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../../include -pthread  -s  -lpthread -ltbb  -o parallel_strings
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 5 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "."
echo "The results will be stored in the file Results_Strings.txt"
echo "."
echo " please, be patient .........."
echo "."
echo "=================================================================="> Results_Strings.txt 2>&1
echo "                B E N C H M A R K    S T R I N G S                  ">> Results_Strings.txt 2>&1
echo ".">> Results_Strings.txt 2>&1
lscpu >> Results_Strings.txt 2>&1
echo "==================================================================">> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 1 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 2 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 3 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 4 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 5 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 6 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 7 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 8 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 9 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 10 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 11 >> Results_Strings.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_strings 12 >> Results_Strings.txt 2>&1


rm input.bin
rm file_generator
rm parallel_strings
echo "."
date
echo "."
echo "E N D"
echo "."
