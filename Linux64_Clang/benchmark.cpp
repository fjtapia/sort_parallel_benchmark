//----------------------------------------------------------------------------
/// @file benchmark.cpp
/// @brief Benchmark of several sort methods with different uint64_t numbers
///
/// @author Copyright (c) 2010 2016 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
///         This program use for comparison purposes, the Threading Building
///         Blocks which license is the GNU General Public License, version 2
///         as  published  by  the  Free Software Foundation.
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

#include "tbb/tbb_stddef.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_sort.h"
#include <parallel_stable_sort/tbb-lowlevel/parallel_stable_sort.h>

#include <boost/sort/spreadsort/spreadsort.hpp>
#include <boost/sort/parallel/sort.hpp>

#include "int_array.hpp"

#define NELEM 100000000
#define NMAXSTRING 10000000
using namespace std ;
namespace bsp_util = boost::sort::parallel::util ;
namespace bs_tools = boost::sort::parallel::tools;
namespace bsort    = boost::sort::parallel ;

using bs_tools::time_point ;
using bs_tools::now;
using bs_tools::subtract_time ;
using bs_tools::fill_vector_uint64;
using bs_tools::write_file_uint64;
using bs_tools::NThread ;

void Generator_sorted(void );
void Generator_uint64(void );
void Generator_string(void) ;

template <class IA>
void Generator (uint64_t N );

template <class IA, class compare  >
int Prueba  ( std::vector <IA> & B , compare comp = compare() );

template <class IA>
int Prueba_spreadsort  ( std::vector <IA> & B );

int main (int argc, char *argv[] )
{   //------------------------------ Inicio ----------------------------------
    cout<<"****************************************************************\n";
    cout<<"**                                                            **\n";
    cout<<"**         B O O S T :: S O R T :: P A R A L L E L            **\n";
    cout<<"**                                                            **\n";
    cout<<"**                   B E N C H M A R K                        **\n";
    cout<<"**                                                            **\n";
    cout<<"****************************************************************\n";
    cout<<std::endl;
    std::cout.flush();
    system ( "lscpu");
    std::cout.flush();
    cout<<"\n";

    Generator_sorted() ;
    Generator_uint64() ;
    Generator_string () ;

    cout<<"================================================================\n";
    cout<<"=                OBJECT COMPARISON                             =\n";
    cout<<"=              ---------------------                           =\n";
    cout<<"=                                                              =\n";
    cout<<"= The objects are arrays of 64 bits numbers                    =\n";
    cout<<"= They are compared in two ways :                              =\n";
    cout<<"=    (H) Heavy : The comparison is the sum of all the numbers  =\n";
    cout<<"=                of the array                                  =\n";
    cout<<"=    (L) Light : The comparison is with the first element of   =\n";
    cout<<"=                the array, as a key                           =\n";
    cout<<"=                                                              =\n";
    cout<<"================================================================\n";
    cout<<"\n\n";
    Generator< int_array<1> >   ( NELEM   );
    Generator< int_array<2> >   ( NELEM>>1);
    Generator< int_array<4> >   ( NELEM>>2);
    Generator< int_array<8> >   ( NELEM>>3);
    Generator< int_array<16> >  ( NELEM>>4);
    Generator< int_array<32> >  ( NELEM>>5);
    Generator< int_array<64> >  ( NELEM>>6);

    return 0 ;
}

void Generator_sorted(void )
{   //---------------------------- begin--------------------------------------
	vector<uint64_t> A  ;

    A.reserve ( NELEM) ;
    cout<<"  "<<NELEM<<" uint64_t elements already sorted\n" ;
    cout<<"=================================================\n";
    A.clear();
    for ( size_t i =0 ; i < NELEM ; ++i)
        A.push_back( i );
    Prueba<uint64_t, std::less<uint64_t> >(A) ;
    Prueba_spreadsort( A);
    cout<<std::endl ;
}
void Generator_uint64(void )
{   //---------------------------- begin--------------------------------------
    vector<uint64_t> A  ;
    A.reserve ( NELEM) ;
    cout<<"  "<< NELEM<<" uint64_t elements randomly filled\n" ;
    cout<<"=================================================\n";
    A.clear();
    if ( fill_vector_uint64("input.bin", A, NELEM) != 0)
    {   std::cout<<"Error in the input file\n";
        return ;
    };
    Prueba<uint64_t, std::less<uint64_t>>(A) ;
    Prueba_spreadsort( A);
    cout<<std::endl ;
}
void Generator_string(void)
{   //------------------------------- begin ----------------------------------
    cout<<"  "<< NMAXSTRING<<" strings randomly filled\n" ;
    cout<<"===============================================\n";
    std::vector <std::string> A ;
    A.reserve ( NMAXSTRING);
    A.clear();
    if ( bs_tools::fill_vector_string("input.bin", A, NMAXSTRING) != 0)
    {   std::cout<<"Error in the input file\n";
        return ;
    };
    Prueba<std::string, std::less<std::string> >(A) ;
    Prueba_spreadsort( A);
    cout<<std::endl ;
};


template <class IA>
void Generator (uint64_t N )
{   //------------------------------- begin ----------------------------------
    bs_tools::uint64_file_generator gen ( "input.bin");
    vector<IA> A ;
   	A.reserve ( N);

    //------------------------ Inicio -----------------------------
    cout<<N<<" elements of size "<<sizeof (IA)<<" randomly filled \n";
    cout<<"=============================================\n";
    gen.reset() ;
    A.clear();
    for ( uint32_t i = 0 ; i < N ; i ++)
        A.emplace_back(IA::generate(gen)) ;
    cout<<"\n  H E A V Y   C O M P A R I S O N\n";
    cout<<"====================================\n";
    Prueba(A , H_comp< IA >()) ;
    cout<<"\n  L I G H T   C O M P A R I S O N \n";
    cout<<"=======================================\n";
    Prueba(A, L_comp< IA> ()) ;
    cout<<std::endl ;
};

template <class IA, class compare  >
int Prueba  ( std::vector <IA> & B , compare comp )
{   //---------------------------- begin --------------------------------
	double duracion ;
	time_point start, finish;
	std::vector <IA> A ( B);

	//--------------------------------------------------------------------
	A = B ;
    cout<<"GCC std::sort                : ";
    start= now() ;
    std::sort (A.begin() , A.end(),comp   );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n";

    A = B ;
    cout<<"Boost sort                   : ";
    start= now() ;
    bsort::sort (A.begin() , A.end(),comp  );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n\n";

    A = B ;
    cout<<"GCC std::stable_sort         : ";
    start= now() ;
    std::stable_sort (A.begin() , A.end(),comp   );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n";

    A = B ;
    cout<<"Boost stable sort            : ";
    start= now() ;
    bsort::stable_sort (A.begin() , A.end(),comp   );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n\n";

    A = B ;
    cout<<"TBB parallel_sort            : ";
    start= now() ;
    tbb::parallel_sort (A.begin() , A.end(),comp );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n";

    A = B ;
    cout<<"Boost parallel sort          : ";
    start= now() ;
    bsort::parallel_sort (A.begin() , A.end(),comp );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n\n";

    A = B ;
    cout<<"Boost parallel stable sort   : ";
    start= now() ;
    bsort::parallel_stable_sort (A.begin() , A.end() ,comp );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n";

    A = B ;
    cout<<"Boost sample sort            : ";
    start= now() ;
    bsort::sample_sort (A.begin() , A.end() ,comp );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n";

    A = B ;
    cout<<"TBB parallel stable sort     : ";
    start= now() ;
    bsort::parallel_stable_sort (A.begin() , A.end(),comp );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n\n";

    return 0 ;
};

template <class IA>
int Prueba_spreadsort  ( std::vector <IA> & B )
{   //---------------------------- Inicio --------------------------------
	double duracion ;
	time_point start, finish;
	std::vector <IA> A ( B);

	//--------------------------------------------------------------------
	A = B ;
    cout<<"Boost spreadsort             : ";
    start= now() ;
    boost::sort::spreadsort::spreadsort (A.begin() , A.end()  );
    finish = now() ;
    duracion = subtract_time(finish ,start) ;
    cout<<duracion<<" secs\n";
    return 0 ;
};

