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

#ifndef PROTOBUF_UTIL_HH
#define PROTOBUF_UTIL_HH

#include <string>
#include <stdexcept>
#include <google/protobuf/util/json_util.h>

namespace protoutil {

  template<class ProtobufType>
  std::string to_json( const ProtobufType & protobuf, const bool pretty_print = false )
  {
    using namespace google::protobuf::util;
    JsonPrintOptions print_options;
    print_options.add_whitespace = pretty_print;
    print_options.always_print_primitive_fields = true;

    std::string ret;
    if ( not MessageToJsonString( protobuf, &ret, print_options ).ok() ) {
      throw std::runtime_error( "cannot convert protobuf to json" );
    }

    return ret;
  }

  template<class ProtobufType>
  void from_json( const std::string & data, ProtobufType & dest )
  {
    using namespace google::protobuf::util;

    if ( not JsonStringToMessage( data, &dest ).ok() ) {
      throw std::runtime_error( "cannot convert json to protobuf" );
    }
  }

  template<class ProtobufType>
  std::string to_string( const ProtobufType & protobuf )
  {
    return protobuf.SerializeAsString();
  }

  template<class ProtobufType>
  void from_string( const std::string & data, ProtobufType & dest )
  {
    dest.ParseFromString( data );
  }

}

#endif /* PROTOBUF_UTIL_HH */
