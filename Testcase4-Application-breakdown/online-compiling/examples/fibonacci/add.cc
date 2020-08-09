//
// Copyright (c) 2020 Institution of Parallel and Distributed System, Shanghai Jiao Tong University
// ServerlessBench is licensed under the Mulan PSL v1.
// You can use this software according to the terms and conditions of the Mulan PSL v1.
// You may obtain a copy of Mulan PSL v1 at:
//     http://license.coscl.org.cn/MulanPSL
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
// PURPOSE.
// See the Mulan PSL v1 for more details.
//

/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <libgen.h>

using namespace std;

int main( int argc, char * argv[] )
{
  if ( argc != 3 ) {
    cerr << "usage: add <A> <B>" << endl;
    return EXIT_FAILURE;
  }

  long long num1, num2;

  ifstream fin_a { argv[ 1 ] };
  ifstream fin_b { argv[ 2 ] };
  ofstream fout { "out" };

  fin_a >> num1;
  fin_b >> num2;
  fout << ( num1 + num2 ) << endl;

  return EXIT_SUCCESS;
}
