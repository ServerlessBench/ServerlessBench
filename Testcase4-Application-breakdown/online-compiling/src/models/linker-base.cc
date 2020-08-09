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

#include "gcc.hh"

#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <iostream>
#include <algorithm>

#include "thunk/ggutils.hh"
#include "thunk/thunk_reader.hh"
#include "util/system_runner.hh"

using namespace std;

vector<string>
GCCModelGenerator::parse_linker_output( const vector<string> & linker_args )
{
  istringstream linker_output { run( linker_args.front(), linker_args, {}, true, true, true, true ) };

  size_t seperator_line_count = 0;

  regex path_regex( "^(?:attempt to open|opened script file|found [^\\s]+ at) "
                    "([^\\s]+)\\s?(?:succeeded|)$" );
  smatch match;
  string line;

  unordered_set<string> dependencies;

  while ( getline( linker_output, line ) ) {
    if ( seperator_line_count < 2 and line[ 0 ] == '=' ) {
      seperator_line_count++;
      continue;
    }
    else if ( seperator_line_count < 2 ) {
      continue;
    }

    regex_match( line, match, path_regex );

    if ( match.size() == 2 ) {
      dependencies.insert( match[ 1 ].str() );
    }
  }

  return { dependencies.begin(), dependencies.end() };
}
