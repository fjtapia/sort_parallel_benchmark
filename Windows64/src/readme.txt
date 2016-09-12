For to execute the test, compile the two programs. And execute the next 
two commands

file_generator input.bin 100000000
benchmark > result.txt 
del input.bin

The first generate a file (input.bin) with random information for the benchmark.
The second execute the benchmark,and store the results in the file result.txt  
The execution time vary from 5 to 20 minutes depending of your computer.
The third command delete the file generated with random information

The program need aroung 2.5 Gigas of memory
