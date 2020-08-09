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

#ifndef ENGINE_LAMBDA_HH
#define ENGINE_LAMBDA_HH

#include <unordered_map>
#include <chrono>

#include "engine.hh"
#include "thunk/thunk.hh"
#include "net/aws.hh"
#include "net/lambda.hh"
#include "net/http_request.hh"

class AWSLambdaExecutionEngine : public ExecutionEngine
{
private:
  AWSCredentials credentials_;
  std::string region_;
  Address address_;
  SSLContext ssl_context_ {};

  size_t running_jobs_ { 0 };
  std::map<uint64_t, std::chrono::steady_clock::time_point> start_times_ {};

  HTTPRequest generate_request( const gg::thunk::Thunk & thunk );

  static float compute_cost( const std::chrono::steady_clock::time_point & begin,
                             const std::chrono::steady_clock::time_point & end = std::chrono::steady_clock::now() );

public:
  AWSLambdaExecutionEngine( const size_t max_jobs,
                            const AWSCredentials & credentials,
                            const std::string & region )
    : ExecutionEngine( max_jobs ), credentials_( credentials ), region_( region ),
      address_( LambdaInvocationRequest::endpoint( region_ ), "https" )
  {}

  void force_thunk( const gg::thunk::Thunk & thunk,
                    ExecutionLoop & exec_loop ) override;

  bool is_remote() const { return true; }
  bool can_execute( const gg::thunk::Thunk & thunk ) const override;
  std::string label() const override { return "\u03bb"; }
  size_t job_count() const override;
};

#endif /* ENGINE_LAMBDA_HH */
