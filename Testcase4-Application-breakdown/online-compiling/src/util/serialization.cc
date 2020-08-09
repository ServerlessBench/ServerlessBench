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

#include "serialization.hh"

#include <fcntl.h>
#include <string>

#include "exception.hh"

using namespace std;

ProtobufDeserializer::ProtobufDeserializer( const string & filename )
  : fin_( CheckSystemCall( filename,
                           open( filename.c_str(), O_RDONLY, 0 ) ) )
{}

ProtobufDeserializer::ProtobufDeserializer( FileDescriptor && fd )
  : fin_( move( fd ) )
{}

string ProtobufDeserializer::read_string( const size_t size )
{
  string ret;
  google::protobuf::io::CodedInputStream coded_input { &raw_input_ };

  if ( not coded_input.ReadString( &ret, size ) ) {
    return "";
  }

  return ret;
}
