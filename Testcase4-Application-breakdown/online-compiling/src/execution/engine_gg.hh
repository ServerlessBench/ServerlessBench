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

#ifndef ENGINE_GG_HH
#define ENGINE_GG_HH

#include "engine.hh"
#include "net/http_request.hh"
#include "thunk/thunk.hh"

class GGExecutionEngine : public ExecutionEngine
{
private:
  Address address_;

  size_t running_jobs_ { 0 };

  HTTPRequest generate_request( const gg::thunk::Thunk & thunk );

public:
  GGExecutionEngine( const size_t max_jobs, const Address & address )
    : ExecutionEngine( max_jobs ), address_( address )
  {}

  void force_thunk( const gg::thunk::Thunk & thunk,
                    ExecutionLoop & exec_loop ) override;
  size_t job_count() const override;

  bool is_remote() const { return true; }
  std::string label() const override { return "remote"; }
  bool can_execute( const gg::thunk::Thunk & ) const { return true; }
};

#endif /* ENGINE_GG_HH */
