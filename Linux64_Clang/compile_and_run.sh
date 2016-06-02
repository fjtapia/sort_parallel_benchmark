clear
echo "=================================================================="
echo "==   B E N C H M A R K    C L A N G     C O M P I L E R         =="
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
clang++ -O3  -std=c++11 -stdlib=libc++ ./file_generator.cpp -march=native -w -fexceptions  -I../include -o file_generator
clang++ -O3  -std=c++11 -stdlib=libc++ ./benchmark.cpp  -march=native -w -fexceptions  -I../../include -I../include -pthread -lpthread -ltbb   -o benchmark
date
echo "R U N N I N G . . . . . . . . . . ."
echo " ( The time needed is around 5 to 20 minutes depending of your machine ). . . . . . ."
./file_generator input.bin 100000000
echo "."
echo "The results will be stored in the file Results.txt"
echo "."
echo " please, be patient .........."
echo "."
./benchmark >Results.txt
rm input.bin
rm file_generator
rm benchmark
date
echo "."
echo "E N D"
echo "."
