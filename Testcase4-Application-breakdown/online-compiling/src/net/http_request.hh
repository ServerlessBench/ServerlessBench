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

#ifndef HTTP_REQUEST_HH
#define HTTP_REQUEST_HH

#include "http_message.hh"

class HTTPRequest : public HTTPMessage
{
private:
    /* for a request, will always be known */
    void calculate_expected_body_size() override;

    /* we have no complex bodies */
    size_t read_in_complex_body( const std::string & str ) override;

    /* connection closed while body was pending */
    bool eof_in_body() const override;

public:
    bool is_head() const;

    using HTTPMessage::HTTPMessage;
};

#endif /* HTTP_REQUEST_HH */
