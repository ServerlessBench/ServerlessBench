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

#ifndef CONNECTION_HH
#define CONNECTION_HH

#include <string>
#include <queue>
#include <iostream>

#include "net/socket.hh"
#include "net/nb_secure_socket.hh"

class ExecutionLoop;

template<class SocketType>
class Connection
{
  friend class ExecutionLoop;

private:
  SocketType socket_ {};
  std::string write_buffer_ {};

public:
  Connection() {}

  Connection( SocketType && sock )
    : socket_( std::move( sock ) )
  {}

  Connection( const Connection & ) = delete;

  ~Connection()
  {
    if ( write_buffer_.size() ) {
      /* std::cerr << "Connection destroyed with data left in write buffer" << std::endl; */
    }
  }

  void enqueue_write( const std::string & str ) { write_buffer_.append( str ); }
  const SocketType & socket() const { return socket_; }
};

using TCPConnection = Connection<TCPSocket>;
using SSLConnection = Connection<NBSecureSocket>;

#endif /* CONNECTION_HH */
