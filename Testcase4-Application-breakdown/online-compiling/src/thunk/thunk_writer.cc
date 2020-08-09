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

#include "thunk_writer.hh"

#include <iostream>
#include <fstream>

#include "thunk/ggutils.hh"
#include "util/digest.hh"
#include "util/path.hh"
#include "util/serialization.hh"

using namespace std;
using namespace gg;
using namespace gg::thunk;

string ThunkWriter::write( const Thunk & thunk, const roost::path & path )
{
  const string serialized_thunk = serialize( thunk );
  const string thunk_hash = gg::hash::compute( serialized_thunk,
                                               ObjectType::Thunk );
  thunk.set_hash( thunk_hash );

  roost::path target_path { ( not path.empty() ) ? path
                                                 : paths::blob( thunk_hash ) };

  if ( not roost::exists( target_path ) ) {
    roost::atomic_create( serialized_thunk, target_path, true, 0400 );
  }

  return thunk_hash;
}

string ThunkWriter::serialize( const gg::thunk::Thunk & thunk )
{
  string ret { MAGIC_NUMBER };
  if ( not thunk.to_protobuf().AppendToString( &ret ) ) {
    throw runtime_error( "could not serialize thunk" );
  }
  return ret;
}
