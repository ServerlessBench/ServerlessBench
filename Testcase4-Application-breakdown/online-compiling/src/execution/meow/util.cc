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

#include "protobufs/gg.pb.h"
#include "protobufs/util.hh"
#include "thunk/ggutils.hh"
#include "util/path.hh"
#include "thunk/thunk.hh"

using namespace std;
using namespace gg;
using namespace meow;
using namespace gg::thunk;

string meow::handle_put_message( const Message & message )
{
  assert( message.opcode() == Message::OpCode::Put );

  const string & data = message.payload();
  ObjectType type = data.compare( 0, thunk::MAGIC_NUMBER.length(), thunk::MAGIC_NUMBER )
                    ? ObjectType::Value
                    : ObjectType::Thunk;

  const string hash = gg::hash::compute( data, type );
  roost::atomic_create( data, gg::paths::blob( hash ) );

  return hash;
}

Message meow::create_put_message( const string & hash )
{
  string requested_file = roost::read_file( gg::paths::blob( hash ) );
  return { Message::OpCode::Put, move( requested_file ) };
}

Message meow::create_execute_message( const Thunk & thunk )
{
  string execution_payload = protoutil::to_string( Thunk::execution_request( thunk ) );
  return { Message::OpCode::Execute, move( execution_payload ) };
}
