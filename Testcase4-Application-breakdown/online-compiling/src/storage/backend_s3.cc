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

#include "backend_s3.hh"

using namespace std;
using namespace storage;

S3StorageBackend::S3StorageBackend( const AWSCredentials & credentials,
                                    const string & s3_bucket,
                                    const string & s3_region )
  : client_( credentials, { s3_region } ), bucket_( s3_bucket )
{}

void S3StorageBackend::put( const std::vector<PutRequest> & requests,
                            const PutCallback & success_callback )
{
  client_.upload_files( bucket_, requests, success_callback );
}

void S3StorageBackend::get( const std::vector<GetRequest> & requests,
                            const GetCallback & success_callback )
{
  client_.download_files( bucket_, requests, success_callback );
}
