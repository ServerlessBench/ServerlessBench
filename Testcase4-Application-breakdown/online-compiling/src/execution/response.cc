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

#include "response.hh"

#include <iostream>
#include <stdexcept>
#include <google/protobuf/util/json_util.h>

#include "protobufs/gg.pb.h"

using namespace std;
using namespace gg;
using namespace google::protobuf::util;

ExecutionResponse ExecutionResponse::parse_message( const std::string & message )
{
  ExecutionResponse response;

  JsonParseOptions parse_options;
  gg::protobuf::ExecutionResponse response_proto;

  if ( not JsonStringToMessage( message, &response_proto ).ok() ) {
    cerr << "invalid response: " << message << endl;
    response.status = JobStatus::OperationalFailure;
    return response;
  }

  response.status = static_cast<JobStatus>( response_proto.return_code() );
  response.stdout = response_proto.stdout();

  if ( response.status != JobStatus::Success ) {
    return response;
  }

  if ( response_proto.executed_thunks_size() != 1 ) {
    throw runtime_error( "current implementation only supports one thunk execution per response" );
  }

  for ( const auto & output_proto : response_proto.executed_thunks( 0 ).outputs() ) {
    response.outputs.push_back( { output_proto.tag(),
                                  output_proto.hash(),
                                  output_proto.size(),
                                  output_proto.executable(),
                                  output_proto.data() } );
  }

  response.thunk_hash = response_proto.executed_thunks( 0 ).thunk_hash();

  return response;
}
