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

#ifndef STORAGE_BACKEND_HH
#define STORAGE_BACKEND_HH

#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "net/requests.hh"
#include "util/optional.hh"
#include "util/path.hh"

typedef std::function<void( const storage::PutRequest & )> PutCallback;
typedef std::function<void( const storage::GetRequest & )> GetCallback;

class StorageBackend
{
protected:
  roost::path remote_index_path_ {};

public:
  virtual void put( const std::vector<storage::PutRequest> & requests,
                    const PutCallback & success_callback = []( const storage::PutRequest & ){} ) = 0;

  virtual void get( const std::vector<storage::GetRequest> & requests,
                    const GetCallback & success_callback = []( const storage::GetRequest & ){} ) = 0;

  bool is_available( const std::string & hash );
  void set_available( const std::string & hash );

  static std::unique_ptr<StorageBackend> create_backend( const std::string & uri );

  virtual ~StorageBackend() {}
};

#endif /* STORAGE_BACKEND_HH */
