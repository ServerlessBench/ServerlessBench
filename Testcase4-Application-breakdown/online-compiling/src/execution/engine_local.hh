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

#ifndef ENGINE_LOCAL_HH
#define ENGINE_LOCAL_HH

#include <thread>

#include "engine.hh"

class LocalExecutionEngine : public ExecutionEngine
{
private:
  bool mixed_ { false };
  size_t running_jobs_ { 0 };

public:
  LocalExecutionEngine( const bool mixed = false,
                        const size_t max_jobs = std::thread::hardware_concurrency() )
    : ExecutionEngine( max_jobs ), mixed_( mixed )
  {}

  void force_thunk( const gg::thunk::Thunk & thunk,
                    ExecutionLoop & exec_loop ) override;
  size_t job_count() const override;

  bool is_remote() const override { return mixed_; }
  std::string label() const override { return "local"; }
  bool can_execute( const gg::thunk::Thunk & ) const override { return true; }
};

#endif /* ENGINE_LOCAL_HH */
