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

#ifndef NET_REDIS_HH
#define NET_REDIS_HH

#include <vector>
#include <string>
#include <functional>

#include "net/requests.hh"

struct RedisClientConfig
{
  std::string ip { "0.0.0.0" };
  uint16_t port { 6379 };

  std::string username {};
  std::string password {};

  size_t max_threads { 32 };
  size_t max_batch_size { 32 };
};

class Redis
{
private:
  RedisClientConfig config_;

public:
  Redis( const RedisClientConfig & config )
    : config_( config )
  {}

  void upload_files( const std::vector<storage::PutRequest> & upload_requests,
                     const std::function<void( const storage::PutRequest & )> & success_callback
                       = []( const storage::PutRequest & ){} );

  void download_files( const std::vector<storage::GetRequest> & download_requests,
                       const std::function<void( const storage::GetRequest & )> & success_callback
                         = []( const storage::GetRequest & ){} );
};

#endif /* NET_REDIS_HH */
