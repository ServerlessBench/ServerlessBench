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

#ifndef STATUS_BAR_HH
#define STATUS_BAR_HH

#include <cstdio>
#include <sys/ioctl.h>
#include <string>

class StatusBar
{
private:
  std::string text_ {};
  winsize window_size_ {};
  StatusBar();

  void init();
  void remove();

public:
  ~StatusBar();

  StatusBar( const StatusBar & ) = delete;
  void operator=( const StatusBar & ) = delete;

  static StatusBar & get();

  static void redraw();
  static void set_text( const std::string & text );
};

#endif /* STATUS_BAR_HH */
