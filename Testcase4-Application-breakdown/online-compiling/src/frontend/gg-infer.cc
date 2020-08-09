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

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "thunk/ggutils.hh"
#include "util/exception.hh"
#include "util/util.hh"

using namespace std;

void usage( const char * argv0 )
{
  cerr << argv0 << " command [args...]" << endl;
}

int main( int argc, char * argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort();
    }

    if ( argc < 2 ) {
      usage( argv[ 0 ] );
      return EXIT_FAILURE;
    }

    gg::paths::blobs();

    string system_path { safe_getenv( "PATH" ) };
    string models_path { safe_getenv( "GG_MODELPATH" ) };

    if ( models_path.empty() ) {
      throw runtime_error( "GG_MODELPATH not set" );
    }

    string new_path = models_path + ":" + system_path;
    setenv( "PATH", new_path.c_str(), true );
    setenv( "GG_REALPATH", system_path.c_str(), true );
    setenv( "GG_BASEPATH", roost::current_working_directory().string().c_str(), false );

    CheckSystemCall( "execvp", execvp( argv[ 1 ], argv + 1 ) );
  }
  catch ( const exception &  e ) {
    print_exception( argv[ 0 ], e );
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
