echo off
cls
echo ==============================================================
echo ==   B E N C H M A R K  V C ++        C O M P I L E R       ==
echo ==                                                          ==
echo ==        B O O S T :: S O R T :: P A R A L L E L           ==
echo ==                                                          ==
echo ==                A L G O R I T H M S                       ==
echo ==                                                          ==
echo ==============================================================
echo .
echo R U N N I N G . . . . . . . . . . .
echo ( The time needed is around 5 to 20 minutes depending of your machine ). . . . . . .
echo .
echo The results will be stored in the file Results.txt
echo .
echo please, be patient ..........
echo .
file_generator input.bin 100000000
fast_benchmark >Results.txt
del input.bin
echo .
echo E N D
echo .
