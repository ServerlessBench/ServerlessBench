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
#include <cstdlib>
#include <unistd.h>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "temp_file.hh"
#include "exception.hh"

using namespace std;

vector<char> to_mutable( const string & str )
{
  vector< char > ret;
  for ( const auto & ch : str ) {
    ret.push_back( ch );
  }
  ret.push_back( 0 ); /* null terminate */

  return ret;
}

/* use mkstemp to get a unique filename on disk */
UniqueFile::UniqueFile( const string & filename_template )
  : mutable_temp_filename_( to_mutable( filename_template + ".XXXXXX" ) ),
    fd_( CheckSystemCall( "mkstemp", mkstemp( &mutable_temp_filename_[ 0 ] ) ) ),
    moved_away_( false )
{
}

/* allow caller to specify filename, but enforce prior nonexistence */
UniqueFile::UniqueFile( const string & filename_prefix, const string & filename_suffix )
  : mutable_temp_filename_( to_mutable( filename_prefix + "." + filename_suffix ) ),
    fd_( CheckSystemCall( "open (" + filename_prefix + "." + filename_suffix + ")",
                          open( &mutable_temp_filename_.front(),
                                O_RDWR | O_CREAT | O_EXCL,
                                S_IRUSR | S_IWUSR ) ) ),
    moved_away_( false )
{}

/* unlike UniqueFile, a TempFile is deleted when object destroyed */
TempFile::~TempFile()
{
  if ( moved_away_ ) { return; }

  try {
    CheckSystemCall( "unlink " + name(), unlink( name().c_str() ) );
  } catch ( const exception & e ) {
    print_exception( "TempFile", e );
  }
}

void UniqueFile::write( const string & contents )
{
  assert( not moved_away_ );

  fd_.write( contents );
}

UniqueFile::UniqueFile( UniqueFile && other )
  : mutable_temp_filename_( other.mutable_temp_filename_ ),
    fd_( move( other.fd_ ) ),
    moved_away_( false )
{
  other.moved_away_ = true;
}

string UniqueFile::name( void ) const
{
  assert( mutable_temp_filename_.size() > 1 );
  return string( mutable_temp_filename_.begin(), mutable_temp_filename_.end() - 1 );
}
