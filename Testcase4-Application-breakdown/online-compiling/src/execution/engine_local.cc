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

#include "engine_local.hh"

#include <stdexcept>

#include "thunk/ggutils.hh"
#include "util/optional.hh"
#include "util/system_runner.hh"

using namespace std;
using namespace gg;
using namespace gg::thunk;

void LocalExecutionEngine::force_thunk( const Thunk & thunk,
                                        ExecutionLoop & exec_loop )
{
  exec_loop.add_child_process( thunk.hash(),
    [this, outputs=thunk.outputs()] ( const uint64_t, const string & hash, const int )
    {
      running_jobs_--; /* XXX not thread-safe */

      vector<ThunkOutput> thunk_outputs;

      for ( const auto & tag : outputs ) {
        Optional<cache::ReductionResult> result = cache::check( gg::hash::for_output( hash, tag ) );

        if ( not result.initialized() ) {
          throw runtime_error( "could not find the reduction entry" );
        }

        thunk_outputs.emplace_back( move( result->hash ), tag );
      }

      success_callback_( hash, move( thunk_outputs ), 0 );
    },
    [mixed=this->mixed_, &thunk]()
    {
      vector<string> command;

      if ( mixed ) {
          command = { "gg-execute", "--get-dependencies", "--put-output",
                      thunk.hash() };
      }
      else {
          command = { "gg-execute", thunk.hash() };
      }

      return ezexec( command[ 0 ], command, {}, true, true );
    },
    true
  );

  running_jobs_++;
}

size_t LocalExecutionEngine::job_count() const
{
  return running_jobs_;
}
