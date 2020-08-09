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

#ifndef PLACEHOLDER_HH
#define PLACEHOLDER_HH

#include <sys/types.h>
#include <string>

#include "util/optional.hh"
#include "util/file_descriptor.hh"

class ThunkPlaceholder
{
public:
  enum class Type { LinkerScript, ShellScript };

private:
  std::string content_hash_;

  void write( const std::string & filename, const Type type ) const;

public:
  ThunkPlaceholder( const std::string & content_hash );

  const std::string & content_hash() const { return content_hash_; }

  void write( const std::string & filename ) const;

  static Optional<ThunkPlaceholder> read( const std::string & filename );
  static bool is_placeholder( FileDescriptor && fd );

  std::string str( const Type type = Type::ShellScript ) const;
};

#endif /* PLACEHOLDER_HH */
