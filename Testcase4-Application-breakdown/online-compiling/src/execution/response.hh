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

#ifndef EXECUTION_RESPONSE_HH
#define EXECUTION_RESPONSE_HH

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <sys/types.h>

#include "util/optional.hh"

class FetchDependenciesError : public std::exception {};
class ExecutionError : public std::exception {};
class UploadOutputError : public std::exception {};

enum class JobStatus
{
  Success = 0,
  RateLimit,
  InvocationFailure,
  OperationalFailure,
  FetchDependenciesFailure,
  ExecutionFailure,
  UploadOutputFailure,
  SocketFailure,
  ChildProcessFailure,
};

class ExecutionResponse
{
public:
  struct Output
  {
    std::string tag;
    std::string hash;
    off_t size;
    bool is_executable;
    std::string data;
  };

private:
  ExecutionResponse() {}

public:
  JobStatus status {};

  std::string thunk_hash {};
  std::vector<Output> outputs {};

  std::string stdout {};

  static ExecutionResponse parse_message( const std::string & message );
};

#endif /* REMOTE_RESPONSE_HH */
