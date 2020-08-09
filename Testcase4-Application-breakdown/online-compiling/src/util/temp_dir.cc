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

#include "temp_dir.hh"

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cassert>

#include "temp_file.hh"
#include "exception.hh"

using namespace std;

UniqueDirectory::UniqueDirectory( const string & dirname_template )
  : mutable_temp_dirname_( to_mutable( dirname_template + ".XXXXXX" ) ),
    moved_away_( false )
{
  if ( mkdtemp( &mutable_temp_dirname_[ 0 ] ) == NULL ) {
    throw unix_error( "mkdtemp " + name() );
  }
}

/* unlike UniqueDirectory, a TempDirectory is deleted when object destroyed */
TempDirectory::~TempDirectory()
{
  if ( moved_away_ ) { return; }

  try {
    CheckSystemCall( "rmdir " + name(), rmdir( name().c_str() ) );
  }
  catch ( const exception & e ) {
    cerr << e.what() << endl;
  }
}

UniqueDirectory::UniqueDirectory( UniqueDirectory && other )
  : mutable_temp_dirname_( other.mutable_temp_dirname_ ),
    moved_away_( false )
{
  other.moved_away_ = true;
}

string UniqueDirectory::name( void ) const
{
  assert( mutable_temp_dirname_.size() > 1 );
  return string( mutable_temp_dirname_.begin(), mutable_temp_dirname_.end() - 1 );
}