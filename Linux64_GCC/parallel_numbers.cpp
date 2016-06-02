//----------------------------------------------------------------------------
/// @file benchmark_sort_04.cpp
/// @brief Benchmark of several sort methods with different uint64_t numbers
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <file_vector.hpp>
#include <time_measure.hpp>

#include <parallel/basic_iterator.h>
#include <parallel/features.h>
#include <parallel/parallel.h>
#include <parallel/algorithm>
#include <omp.h>

#include "tbb/tbb_stddef.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_sort.h"
#include <parallel_stable_sort/tbb-lowlevel/parallel_stable_sort.h>

#include <boost/sort/parallel/sort.hpp>
#include <boost/sort/spreadsort/integer_sort.hpp>

#define NELEM 100000000
using namespace std ;

namespace bs_util = boost::sort::parallel::detail::util ;
namespace bs_par = boost::sort::parallel ;

using bs_util::time_point ;
using bs_util::now;
using bs_util::subtract_time ;
using bs_util::fill_vector_uint64;
using bs_util::write_file_uint64;


using namespace __gnu_parallel;
//std::mt19937_64 my_rand(0);

int Test ( int option) ;
vector<uint64_t> A  ;

int main (int argc, char *argv[] )
{   //------------------------------ Inicio ----------------------------------
    int option  =0 ;
    if ( argc > 1) option = atoi ( argv[1]);
    if ( option == 0 )
    {   //----------------------------- menu ---------------------------------
        std::cout<<std::endl<<std::endl ;
        std::cout<<std::endl<<std::endl ;
        std::cout<<"\t      M E N U \n";
        std::cout<<"\t    =============\n\n\n";
        std::cout<<"\t 1.- std::sort \n";
        std::cout<<"\t 2.- boost sort \n";
        std::cout<<"\t 3.- std::stable_sort \n";
        std::cout<<"\t 4.- boost stable_sort \n";
        std::cout<<"\t 5.- boost spreadsort \n";
        std::cout<<"\t 6.- GCC   parallel sort \n";
        std::cout<<"\t 7.- tbb   parallel sort \n";
        std::cout<<"\t 8.- boost parallel_sort \n";
        std::cout<<"\t 9.- GCC   parallel stable sort \n";
        std::cout<<"\t10.- boost parallel stable sort \n";
        std::cout<<"\t11.- boost sample sort \n";
        std::cout<<"\t12.- tbb   lowlevel parallel stable sort \n";

        std::cout<<std::endl<<std::endl ;
        std::cout<<"\t Select option -> ";
        std::cin>>option ;
        cout<<"\n";
    };
    if ( option < 1 or option > 12 ) return 0 ;
    //------------------------------------------------------------------------
    //        LOAD THE DATA FROM THE FILE
    //------------------------------------------------------------------------
	A.reserve ( NELEM);
    cout<<"\n";
    //------------------------ Inicio -----------------------------
    switch ( option)
    {  	case 1 :
			cout<<"GCC Sort (not stable sort)\n";
			break ;
		case 2 :
			cout<<"Boost Sort (not stable sort)\n";
			break ;
		case 3 :
			cout<<"GCC Stable Sort (stable sort)\n";
			break ;
		case 4 :
			cout<<"Boost Stable Sort (stable sort)\n";
			break ;
		case 5 :
			cout<<"Boost Spreadsort (not stable sort)\n";
			break ;
    	case 6 :
            cout<<"GCC Parallel Sort (not stable sort)\n";
            break ;
        case 7 :
            cout<<"TBB Parallel Sort (not stable sort)\n";
            break ;
        case 8 :
            cout<<"Boost Parallel Sort (non stable sort)\n";
             break ;
        case 9 :
            cout<<"GCC Parallel Stable Sort (stable sort)\n";
            break ;
        case 10 :
            cout<<"Boost Parallel Stable Sort (stable sort)\n";
            break ;
        case 11 :
            cout<<"Boost Sample Sort (stable sort)\n";
            break ;
        case 12 :
            cout<<"TBB Parallel Stable Sort (stable sort)\n";
             break ;
    } ;
    cout<<"Sorting of "<< NELEM<<" uint64_t elements : " ;

    A.clear();
    if ( bs_util::fill_vector_uint64("input.bin", A, NELEM) != 0)
    {   std::cout<<"Error in the input file\n";
        return 1 ;
    };
    Test(option) ;

    return 0 ;
};

int Test ( int option)
{   //---------------------------- Inicio --------------------------------
	double duracion ;
	time_point start, finish;
    std::less<uint64_t> comp ;

	//--------------------------------------------------------------------
    switch ( option )
    {
    case 1:
        start= now() ;
        std::sort (A.begin() , A.end()  );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 2 :
        //cout<<"---------------- boost::sort::intro_sort --------------\n";
        start= now() ;
        bs_par::sort (A.begin() , A.end() );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 3 :
        start= now() ;
        std::stable_sort (A.begin() , A.end()  );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 4 :
        //cout<<"--------------------- boost stable_sort -----------------\n";
        start= now() ;
        bs_par::stable_sort (A.begin() , A.end()  );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 5 :
        //cout<<"--------------------- spreadsort------------------------\n";
        start= now() ;
        boost::sort::spreadsort::integer_sort (A.begin() , A.end()  );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 6:
        //----------------- __gnu_parallel::sort ------------------------";
        start= now() ;
        __gnu_parallel::sort (A.begin() , A.end());
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 7 :
        //------------------- tbb::parallel_sort -----------------------------
        start= now() ;
        tbb::parallel_sort (A.begin() , A.end()  );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 8 :
        //-------------- boost::sort::parallel::parallel_sort-----------
        start= now() ;
        bs_par::parallel_sort (A.begin() , A.end() );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 9 :
        //------------------- __gnu_parallel::stable_sort --------------------
        start= now() ;
        __gnu_parallel::stable_sort (A.begin() , A.end()  );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 10 :
        //-------- boost::sort::parallel::parallel_stable_sort ------------
        start= now() ;
        bs_par::parallel_stable_sort (A.begin() , A.end()  );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 11 :
        //--------------------- boost::sort::parallel::sample_sort ------------
        start= now() ;
        bs_par::sample_sort (A.begin() , A.end()  );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;

    case 12 :
        //--------------------- tbb lowlevel parallel_stable_sort ------------
        start= now() ;
        pss::parallel_stable_sort (A.begin() , A.end(),comp );
        finish = now() ;
        duracion = subtract_time(finish ,start) ;
        cout<<duracion<<" secs\n";
        break ;
    };
    return 0 ;
};
