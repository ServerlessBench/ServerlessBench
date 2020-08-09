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

#include "timeit.hh"

#include <chrono>

using namespace std;

template<class TimeUnit>
TimeUnit time_it( const function<void()> & f )
{
  chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();
  f();
  chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
  return chrono::duration_cast<TimeUnit>( end - begin );
}

template chrono::milliseconds time_it( const function<void()> & f );
