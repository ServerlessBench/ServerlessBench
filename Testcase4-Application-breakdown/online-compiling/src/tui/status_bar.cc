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

#include "status_bar.hh"

#include <cstdio>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#define HIDE_CURSOR "\033[25l"
#define SHOW_CURSOR "\033[25h"

StatusBar::StatusBar()
{
  init();
}

StatusBar::~StatusBar()
{
  remove();
}

StatusBar & StatusBar::get()
{
  static StatusBar status_bar;
  return status_bar;
}

void StatusBar::init()
{
  ioctl( STDOUT_FILENO, TIOCGWINSZ, &window_size_ );

  ostringstream oss;
  oss << "\n\0337\033[1;" << window_size_.ws_row - 1 << "r\033["
      << window_size_.ws_row << ";1H\033[2K\0338\033[1A";

  cerr << oss.str() << flush;
}

void StatusBar::remove()
{
  set_text( "" );
  cerr << "\0337\033[1;" << window_size_.ws_row << "r\0338" << flush;
}

void StatusBar::redraw()
{
  get().remove();
  get().init();
  get().set_text( get().text_ );
}

void StatusBar::set_text( const string & text )
{
  StatusBar & status_bar = get();
  status_bar.text_ = text;

  ostringstream oss;
  oss << HIDE_CURSOR
      << "\0337\033[" << status_bar.window_size_.ws_row << ";1H\033[K"
      << status_bar.text_
      << "\033[K\0338"
      << SHOW_CURSOR;

  cerr << oss.str() << flush;
}
