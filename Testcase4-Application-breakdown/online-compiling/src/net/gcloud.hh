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

#ifndef GCLOUD_HH
#define GCLOUD_HH

#include <string>

class GoogleStorageCredentials
{
private:
  std::string access_key_;
  std::string secret_key_;

public:
  GoogleStorageCredentials();
  GoogleStorageCredentials( const std::string & access_key,
                            const std::string & secret_key );

  const std::string & access_key() const { return access_key_; }
  const std::string & secret_key() const { return secret_key_; }
};

#endif /* GCLOUD_HH */
