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

#ifndef AWSV4_SIG_HH
#define AWSV4_SIG_HH

#include <map>
#include <string>
#include <vector>

class AWSv4Sig {
  private:
    static std::vector<uint8_t> derive_signing_key_(const std::string &secret,
                                                    const std::string &date,
                                                    const std::string &region,
                                                    const std::string &service);
    static std::string sha256buf_to_string_(const unsigned char *buf);
    static std::string sha256_(const std::string &in);

  public:
    static void sign_request(const std::string &first_line,
                             const std::string &secret,
                             const std::string &akid,
                             const std::string &region,
                             const std::string &service,
                             const std::string &request_date,
                             const std::string &payload,
                             std::map<std::string, std::string> &headers,
                             const std::string & payload_hash = {});
};

#endif /* AWSV4_SIG_HH */
