<H1>Benchmark Boost Sort Parallel</H1>
<H2> <a href="https://github.com/fjtapia/sort_parallel_benchmark">https://github.com/fjtapia/sort_parallel_benchmark</a> </H2>


This library is the benchmark for to measure the speed of the [Boost Sort Parallel](https://github.com/fjtapia/sort_parallel)	 algorithms compared with the GCC Parallel algorithms , the Intel Threading Building Blocks (TBB)  algorithms and the Microsoft PPC  Libraries.

This project is not included in the Boost Sort Parallel Library, because use code  of external sources as TBB , GCC and Microsoft PPC.

The external programs used are :

* Threading Building Blocks ( TBB )
* OpenMP of the GCC compiler
* [TBB experimental parallel_stable_sort](https://software.intel.com/sites/default/files/managed/48/9b/parallel_stable_sort.zip)

In this library is included ALL the code needed for to compile and run the benchmark. You don't need load the Boost Sort Parallel Library. It's inside the include folder, with the external code.

For to compile and run the Linux64 GCC and CLANG version , need to have installed the TBB package. ( Probably is in your package repository).

You have folders with the different operating system and compiler used.

Inside the Linux64_GCC and Linux64_CLANG folders, you can find the source code and  shell scripts for to compile and run the benchmark. The time needed by all depend between 10 and 20 min depending of your machine. 

The program generate a file of 800 M (input.bin) with the random information used in the benchmark. When finish, this file is deleted

The Linux64_CLANG don't use the GCC Parallel sort and GCC Parallel Stable sort  due to the problems with the OpenMP of the version used (4.7).

In the Windows64 you can find the source code of the benchmark and a version compiled with the Visual Studio 2015.

The execution of the benchmark generate an output file, beginning with the description of the machine (number of threads, memory, cache .... ), and a description of each test and the results obtained

Inside the folders. you can find, too, a sub folder results, with the results files obtained in several machines

***
*Copyright 2016  [Francisco Tapia (fjtapia@gmail.com) ] (mail:fjtapia@gmail.com)*
