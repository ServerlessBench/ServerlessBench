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

#include "mime_type.hh"
#include "util/exception.hh"
#include "util/tokenize.hh"

using namespace std;

MIMEType::MIMEType( const string & content_type )
  : type_(), parameters_()
{
  auto type_and_parameters = split( content_type, ";" );
  if ( type_and_parameters.size() == 0
       or type_and_parameters.at( 0 ).empty() ) {
    throw runtime_error( "MIMEType: invalid MIME media-type string" );
  }

  type_ = type_and_parameters.at( 0 );
  /* XXX don't parse the parameters for now */
}
