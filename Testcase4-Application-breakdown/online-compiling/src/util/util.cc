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

#include "util.hh"

#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;

string safe_getenv( const string & key )
{
  const char * const value = getenv( key.c_str() );
  if ( not value ) {
    throw runtime_error( "missing environment variable: " + key );
  }
  return value;
}

string safe_getenv_or( const string & key, const string & def_val )
{
  const char * const value = getenv( key.c_str() );
  if ( not value ) {
    return def_val;
  }
  return value;
}

string format_bytes( size_t bytes )
{
  const char * sizes[] = { "B", "KiB", "MiB", "GiB", "TiB" };
  double val = bytes;

  size_t i;
  for ( i = 0; i < 4 and bytes >= 1024; i++, bytes /= 1024 ) {
    val = bytes / 1024.0;
  }

  ostringstream oss;
  oss << fixed << setprecision( 1 ) << val << " " << sizes[ i ];
  return oss.str();
}
