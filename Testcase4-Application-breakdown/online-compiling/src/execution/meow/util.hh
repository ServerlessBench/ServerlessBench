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

#ifndef MEOW_UTIL_HHs
#define MEOW_UTIL_HHs

#include <memory>

#include "execution/connection.hh"
#include "execution/meow/message.hh"
#include "thunk/thunk.hh"

namespace meow {

  std::string handle_put_message( const Message & message );
  Message create_put_message( const std::string & hash );
  Message create_execute_message( const gg::thunk::Thunk & thunk );

}

#endif /* MEOW_UTIL_HHs */
