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

#ifndef S3_HH
#define S3_HH

#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "aws.hh"
#include "http_request.hh"
#include "requests.hh"
#include "util/path.hh"
#include "util/optional.hh"

class S3
{
public:
  static std::string endpoint( const std::string & region,
                               const std::string & bucket );
};

class S3PutRequest : public AWSRequest
{
public:
  S3PutRequest( const AWSCredentials & credentials,
                const std::string & endpoint, const std::string & region,
                const std::string & object, const std::string & contents,
                const std::string & content_hash = {} );
};

class S3GetRequest : public AWSRequest
{
public:
  S3GetRequest( const AWSCredentials & credentials,
                const std::string & endpoint, const std::string & region,
                const std::string & object );
};

struct S3ClientConfig
{
  std::string region { "us-west-1" };
  std::string endpoint {};
  size_t max_threads { 32 };
  size_t max_batch_size { 32 };
};

class S3Client
{
private:
  AWSCredentials credentials_;
  S3ClientConfig config_;

public:
  S3Client( const AWSCredentials & credentials,
            const S3ClientConfig & config = {} );

  void download_file( const std::string & bucket,
                      const std::string & object,
                      const roost::path & filename );

  void upload_files( const std::string & bucket,
                     const std::vector<storage::PutRequest> & upload_requests,
                     const std::function<void( const storage::PutRequest & )> & success_callback
                       = []( const storage::PutRequest & ){} );

  void download_files( const std::string & bucket,
                       const std::vector<storage::GetRequest> & download_requests,
                       const std::function<void( const storage::GetRequest & )> & success_callback
                         = []( const storage::GetRequest & ){} );
};

#endif /* S3_HH */
