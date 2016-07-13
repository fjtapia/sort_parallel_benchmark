//----------------------------------------------------------------------------
/// @file file_generator.cpp
/// @brief : this program create a file with random information, for to be
///          used in the benchmarks.
///          The invocation format is :
///          file_generator filename number_of_64_bits_elements
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
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <file_vector.hpp>
#include <vector>


using std::cout;
using std::endl;
namespace bs_tools = boost::sort::parallel::tools;

void print_banner( );

int main ( int argc, char * argv [ ] )
{   //---------------------------- begin--------------------------------------
    std::string name;
    size_t number;

    if ( argc < 3)
    {   cout<<"This program generate a file filled with random numbers\n";
        cout<<"of 64 bits\n";
        cout<<"The invocation format is :\n";
        cout<<" file_generator file_name number_elements\n\n";
        return 0;
    };
    name =  argv [ 1 ];
    number = atoi ( argv [ 2 ] );
    if ( number == 0 )
    {   cout<<"error, the number can't be zero\n";
        return 0;
    };

    if ( bs_tools::generate_file ( name, number ) != 0)
        std::cout<<"Error in the file creation\n";
    return 0;
};
void print_banner( )
{   //---------------------------- begin -------------------------------------
    cout<<" The format of this program is :\n";
    cout<<" file_generator filename number_elements\n\n";
    cout<<" The elements are 64 bits random numbers\n";
};
