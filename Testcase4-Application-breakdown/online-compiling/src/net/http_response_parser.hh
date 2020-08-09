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

#ifndef HTTP_RESPONSE_PARSER_HH
#define HTTP_RESPONSE_PARSER_HH

#include "http_message_sequence.hh"
#include "http_response.hh"
#include "http_request.hh"

class HTTPResponseParser : public HTTPMessageSequence<HTTPResponse>
{
private:
    /* Need this to handle RFC 2616 section 4.4 rule 1 */
    std::queue<HTTPRequest> requests_ {};

    void initialize_new_message() override;

public:
    void new_request_arrived( const HTTPRequest & request );
    unsigned int pending_requests() const { return requests_.size(); }
};

#endif /* HTTP_RESPONSE_PARSER_HH */
