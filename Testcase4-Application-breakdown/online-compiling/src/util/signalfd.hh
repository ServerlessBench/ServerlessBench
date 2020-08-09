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

#ifndef SIGNALFD_HH
#define SIGNALFD_HH

#include <sys/signalfd.h>
#include <initializer_list>

#include "file_descriptor.hh"

/* wrapper class for Unix signal masks and signal file descriptor */

class SignalMask
{
private:
  sigset_t mask_;

public:
  SignalMask( const std::initializer_list<int> signals );
  const sigset_t & mask( void ) const { return mask_; }
  void set_as_mask( void ) const;

  static SignalMask current_mask( void );
  bool operator==( const SignalMask & other ) const;
};

class SignalFD
{
private:
  FileDescriptor fd_;

public:
  SignalFD( const SignalMask & signals );

  FileDescriptor & fd( void ) { return fd_; }
  signalfd_siginfo read_signal( void ); /* read one signal */
};

#endif /* SIGNALFD_HH */
