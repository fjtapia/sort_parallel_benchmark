clear
echo "==================================================================" 
echo "==              B E N C H M A R K   N U M B E R S               ==" 
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
g++ ./file_generator.cpp -std=c++11 -march=native -w -fexceptions -O3 -I../../include  -I../include  -s  -o file_generator
g++ ./parallel_numbers.cpp -std=c++11 -march=native -w -fexceptions -fopenmp -O3 -I../../include -I../include  -pthread  -s  -lpthread -ltbb  -o parallel_numbers
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 5 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "."
echo "The results will be stored in the file Results_Numbers.txt"
echo "."
echo " please, be patient .........."
echo "."
echo "=================================================================="> Results_Numbers.txt 2>&1
echo "                B E N C H M A R K   N U M B E R S                 ">> Results_Numbers.txt 2>&1
echo ".">> Results_Numbers.txt 2>&1
lscpu >> Results_Numbers.txt 2>&1
echo "==================================================================">> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 1 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 2 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 3 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 4 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 5 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 6 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 7 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 8 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 9 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 10 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 11 >> Results_Numbers.txt 2>&1
/usr/bin/time -f "%M KB used" ./parallel_numbers 12 >> Results_Numbers.txt 2>&1

rm input.bin
rm file_generator
rm parallel_numbers
echo "."
date
echo "."
echo "E N D"
echo "."
