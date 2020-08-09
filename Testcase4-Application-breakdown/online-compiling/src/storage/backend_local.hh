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

#ifndef STORAGE_BACKEND_LOCAL_HH
#define STORAGE_BACKEND_LOCAL_HH

#include "backend.hh"
#include "net/aws.hh"
#include "net/s3.hh"

class LocalStorageBackend : public StorageBackend
{
public:
  LocalStorageBackend() {}

  void put( const std::vector<storage::PutRequest> &,
            const PutCallback & = []( const storage::PutRequest & ){} ) {}

  void get( const std::vector<storage::GetRequest> &,
            const GetCallback & = []( const storage::GetRequest & ){} ) {}
};

#endif /* STORAGE_BACKEND_LOCAL_HH */
