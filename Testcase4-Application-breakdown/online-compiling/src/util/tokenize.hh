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

#ifndef TOKENIZE_HH
#define TOKENIZE_HH

#include <string>
#include <vector>

static std::vector< std::string > split( const std::string & str, const std::string & separator )
{
  std::vector< size_t > indices;

  size_t next_token = 0;
  while ( (next_token = str.find( separator, next_token )) != std::string::npos ) {
    indices.push_back( next_token );
    next_token++;
  }

  if ( indices.empty() ) {
    return { str };
  }

  std::vector< std::string > ret;

  /* first token */
  ret.push_back( str.substr( 0, indices[ 0 ] ) );

  /* inner tokens */
  for ( size_t i = 0; i < indices.size() - 1; i++ ) {
    ret.push_back( str.substr( indices[ i ] + separator.size(),
                  indices[ i + 1 ] - indices[ i ] - separator.size() ) );
  }

  /* last token */
  ret.push_back( str.substr( indices.back() + separator.size() ) );

  return ret;
}

#endif /* TOKENIZE_HH */
