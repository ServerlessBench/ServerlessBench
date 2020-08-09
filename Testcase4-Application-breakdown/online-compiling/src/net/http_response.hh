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

#ifndef HTTP_RESPONSE_HH
#define HTTP_RESPONSE_HH

#include <memory>

#include "http_message.hh"
#include "body_parser.hh"
#include "http_request.hh"

class HTTPResponse : public HTTPMessage
{
private:
    HTTPRequest request_ {};

    /* required methods */
    void calculate_expected_body_size() override;
    size_t read_in_complex_body( const std::string & str ) override;
    bool eof_in_body() const override;

    std::unique_ptr<BodyParser> body_parser_ { nullptr };

public:
    void set_request( const HTTPRequest & request );
    const HTTPRequest & request() const { return request_; }

    std::string status_code() const;

    using HTTPMessage::HTTPMessage;
};

#endif /* HTTP_RESPONSE_HH */
