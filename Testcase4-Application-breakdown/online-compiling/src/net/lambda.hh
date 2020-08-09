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

#ifndef LAMBDA_HH
#define LAMBDA_HH

#include <string>

#include "aws.hh"

class LambdaInvocationRequest : public AWSRequest
{
public:
  enum class InvocationType { EVENT, REQUEST_RESPONSE, DRY_RUN };
  enum class LogType { NONE, TAIL };

  static std::string endpoint( const std::string & region );

  LambdaInvocationRequest( const AWSCredentials & credentials,
                           const std::string & region,
                           const std::string & function_name,
                           const std::string & payload,
                           const InvocationType invocation_type = InvocationType::REQUEST_RESPONSE,
                           const LogType & log_type = LogType::NONE,
                           const std::string & context = "e30=" /* base64( "{}" ) */ );
};

#endif /* LAMBDA_HH */
