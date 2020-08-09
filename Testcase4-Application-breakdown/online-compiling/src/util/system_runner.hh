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

#ifndef SYSTEM_RUNNER_HH
#define SYSTEM_RUNNER_HH

#include <vector>
#include <string>

int ezexec( const std::string & filename,
            const std::vector<std::string> & args,
            const std::vector<std::string> & env,
            const bool use_environ = false,
            const bool path_search = false );

std::string run( const std::string & filename,
                 const std::vector<std::string> & args,
                 const std::vector<std::string> & env,
                 const bool use_environ = false,
                 const bool path_search = false,
                 const bool read_stdout_until_eof = false,
                 const bool suppress_errors = false );

std::string command_str( const std::vector<std::string> & command,
                         const std::vector<std::string> & environment );

std::string command_str( const int argc, char * argv[] );

#endif /* SYSTEM_RUNNER_HH */
