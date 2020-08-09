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

#ifndef UTIL_IPC_SOCKET_HH
#define UTIL_IPC_SOCKET_HH

#include <string>

#include "file_descriptor.hh"

/* Unix domain socket */
class IPCSocket : public FileDescriptor
{
public:
  IPCSocket();

  void bind( const std::string & path );
  void connect( const std::string & path );

  void listen( const int backlog = 200 );
  FileDescriptor accept( void );
};

#endif /* UTIL_IPC_SOCKET_HH */
