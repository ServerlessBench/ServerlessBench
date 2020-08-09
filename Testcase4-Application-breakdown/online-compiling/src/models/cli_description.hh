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

#ifndef CLI_DESCRIPTION_HH
#define CLI_DESCRIPTION_HH

#include <string>
#include <vector>
#include <limits>

#include "util/optional.hh"

/* See also: http://docopt.org/ */

/* An example for a description string:
   path-to-static-bins/vpxenc -i,--input=@infile @outfile
*/

struct CLIOption
{
  int value { 0 };

  Optional<char> short_opt {};
  Optional<std::string> long_opt {};

  enum class Type { DoNotCare, InFile, OutFile } type { Type::DoNotCare };
};

class CLIDescription
{
private:
  std::string target_bin_ {};
  std::vector<CLIOption> options_ {};
  std::vector<size_t> infile_args_ {};
  std::vector<size_t> outfile_args_ {};

public:
  CLIDescription( const std::string & description );

  const std::string & target_bin() const { return target_bin_; }
  const std::vector<CLIOption> & options() const { return options_; }
  const std::vector<size_t> & infile_args() const { return infile_args_; }
  const std::vector<size_t> & outfile_args() const { return outfile_args_; }
};

#endif /* CLI_DESCRIPTION_HH */
