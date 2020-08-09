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

#ifndef SERIALIZATION_HH
#define SERIALIZATION_HH

#include <string>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "file_descriptor.hh"

class ProtobufDeserializer
{
protected:
  FileDescriptor fin_;
  google::protobuf::io::FileInputStream raw_input_ { fin_.fd_num() };

public:
  ProtobufDeserializer( const std::string & filename );
  ProtobufDeserializer( FileDescriptor && fd );
  std::string read_string( const size_t size );

  template<class EntryProtobufType>
  bool read_protobuf( EntryProtobufType & protobuf );
};

template<class EntryProtobufType>
bool ProtobufDeserializer::read_protobuf( EntryProtobufType & message )
{
  google::protobuf::io::CodedInputStream coded_input { &raw_input_ };

  if ( message.ParseFromCodedStream( &coded_input ) ) {
    return true;
  }

  return false;
}


#endif /* SERIALIZATION_HH */
