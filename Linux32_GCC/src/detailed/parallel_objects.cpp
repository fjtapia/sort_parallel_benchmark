//----------------------------------------------------------------------------
/// @file  parallel_objects.cpp
/// @brief Benchmark of several sort methods with different object formats 
///        and sizes
///
/// @author Copyright (c) 2016 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <vector>

#include <omp.h>
#include <parallel/algorithm>
#include <parallel/basic_iterator.h>
#include <parallel/features.h>
#include <parallel/parallel.h>

#include "tbb/parallel_sort.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tbb_stddef.h"
#include <parallel_stable_sort/tbb-lowlevel/parallel_stable_sort.h>

#include "int_array.hpp"
#include <boost/sort/parallel/sort.hpp>
#include <file_vector.hpp>
#include <time_measure.hpp>

#define NELEM 50000000
using namespace std;

namespace bs_util = boost::sort::parallel::detail::util;
namespace bs_par = boost::sort::parallel;

using bs_util::time_point;
using bs_util::now;
using bs_util::subtract_time;
using bs_util::fill_vector_uint64;
using bs_util::write_file_uint64;

// std::mt19937_64 my_rand(0);

template <class IA, class compare>
int Test(std::vector<IA> &A, compare comp, int option);

template <class IA>
void Generator(uint64_t N, int option);

int main(int argc, char *argv[])
{ //------------------------------ Inicio ----------------------------------
    int option = 0;
    if (argc > 1) option = atoi(argv[1]);
    if (option == 0)
    {   //----------------------------- menu ---------------------------------
        cout << "=========================================================\n";
        cout << "=            OBJECT COMPARISON                          =\n";
        cout << "=          ---------------------                        =\n";
        cout << "=                                                       =\n";
        cout << "= The objects are arrays of 64 bits numbers             =\n";
        cout << "= They are compared in two ways :                       =\n";
        cout << "= (H) Heavy : The comparison is the sum of all the      =\n";
        cout << "=             numbers of the array                      =\n";
        cout << "= (L) Light : The comparison is with the first          =\n";
        cout << "=             element of the array, as a key            =\n";
        cout << "=                                                       =\n";
        cout << "========================================================\n";
        cout << "\n\n";
        cout << std::endl << std::endl;
        cout << std::endl << std::endl;
        cout << "\t      M E N U \n";
        cout << "\t    =============\n\n\n";
        cout << "\t 1.- std::sort \n";
        cout << "\t 2.- boost introsort \n";
        cout << "\t 3.- std::stable_sort \n";
        cout << "\t 4.- boost stable_sort \n";
        cout << "\t 5.- GCC   parallel sort \n";
        cout << "\t 6.- tbb   parallel sort \n";
        cout << "\t 7.- boost parallel_sort \n";
        cout << "\t 8.- GCC   parallel stable sort \n";
        cout << "\t 9.- boost parallel stable sort \n";
        cout << "\t10.- boost sample sort \n";
        cout << "\t11.- tbb   parallel stable sort \n";

        std::cout << std::endl << std::endl;
        std::cout << "\t Select option -> ";
        std::cin >> option;
        cout << "\n";
    };
    if (option < 1 or option > 11) return 0;
    //------------------------------------------------------------------------
    //        LOAD THE DATA FROM THE FILE
    //------------------------------------------------------------------------
    cout << endl;
    //------------------------ Inicio -----------------------------
    switch (option)
    {
        case 1: cout << "GCC Sort (not stable sort)\n"; break;
        case 2: cout << "Boost Sort (not stable sort)\n"; break;
        case 3: cout << "GCC Stable Sort (stable sort)\n"; break;
        case 4: cout << "Boost Stable Sort (stable sort)\n"; break;
        case 5: cout << "GCC Parallel Sort (not stable sort)\n"; break;
        case 6: cout << "TBB Parallel Sort (not stable sort)\n"; break;
        case 7: cout << "Boost Parallel Sort (non stable sort)\n"; break;
        case 8: cout << "GCC Parallel Stable Sort (stable sort)\n"; break;
        case 9: cout << "Boost Parallel Stable Sort (stable sort)\n"; break;
        case 10: cout << "Boost Sample Sort (stable sort)\n"; break;
        case 11: cout << "TBB Parallel Stable Sort (stable sort)\n"; break;
    };
    cout << endl;
    //------------------------------------------------------------------------
    // Execution with different object format
    //------------------------------------------------------------------------
    Generator<int_array<1>>(NELEM, option);
    Generator<int_array<2>>(NELEM >> 1, option);
    Generator<int_array<4>>(NELEM >> 2, option);
    Generator<int_array<8>>(NELEM >> 3, option);
    Generator<int_array<16>>(NELEM >> 4, option);
    Generator<int_array<32>>(NELEM >> 5, option);
    Generator<int_array<64>>(NELEM >> 6, option);

    return 0;
}

template <class IA>
void Generator(uint64_t N, int option)
{ //------------------------------- begin ----------------------------------
    bs_util::uint64_file_generator gen("input.bin");
    vector<IA> A;
    A.reserve(N);
    IA Aux;

    cout << "\Sort of N = " << N << " elements of size " << sizeof(IA) << "\n";

    cout << "Heavy Comparison   : ";
    gen.reset();
    A.clear();
    for (uint32_t i = 0; i < N; i++) A.emplace_back(IA::generate(gen));
    Test(A, H_comp<IA>(), option);

    cout << "Light Comparison   : ";
    gen.reset();
    A.clear();
    for (uint32_t i = 0; i < N; i++) A.emplace_back(IA::generate(gen));
    Test(A, L_comp<IA>(), option);
    cout << endl;
};

template <class IA, class compare>
int Test(std::vector<IA> &A, compare comp, int option)
{ 
    double duracion;
    time_point start, finish;

    switch (option)
    {
        case 1:
            start = now();
            std::sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 2:
            start = now();
            bs_par::sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 3:
            start = now();
            std::stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 4:
            start = now();
            bs_par::stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 5:
            start = now();
            __gnu_parallel::sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 6:
            start = now();
            tbb::parallel_sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 7:
            start = now();
            bs_par::parallel_sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 8:
            start = now();
            __gnu_parallel::stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 9:
            start = now();
            bs_par::parallel_stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 10:
            start = now();
            bs_par::sample_sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;

        case 11:
            start = now();
            pss::parallel_stable_sort(A.begin(), A.end(), comp);
            finish = now();
            duracion = subtract_time(finish, start);
            cout << duracion << " secs\n";
            break;
    };
    return 0;
};
