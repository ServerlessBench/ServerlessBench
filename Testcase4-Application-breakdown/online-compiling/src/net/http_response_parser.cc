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

/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <string>
#include <cassert>

#include "http_response_parser.hh"
#include "http_response.hh"
#include "util/exception.hh"

using namespace std;

void HTTPResponseParser::initialize_new_message()
{
    /* do we have a request that we can match this response up with? */
    if ( requests_.empty() ) {
        throw runtime_error( "HTTPResponseParser: response without matching request" );
    }

    message_in_progress_.set_request( requests_.front() );

    requests_.pop();
}

void HTTPResponseParser::new_request_arrived( const HTTPRequest & request )
{
    requests_.push( request );
}
