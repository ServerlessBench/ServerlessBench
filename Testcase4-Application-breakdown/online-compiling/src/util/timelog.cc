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

#include "util/timelog.hh"

#include <sstream>

using namespace std;
using namespace std::chrono;

TimeLog::TimeLog()
  : start_( duration_cast<milliseconds>( system_clock::now().time_since_epoch() ) ),
    prev_( start_ )
{}

void TimeLog::add_point( const std::string & title )
{
  auto now = duration_cast<milliseconds>( system_clock::now().time_since_epoch() );

  points_.emplace_back( title, now - prev_ );
  prev_ = now;
}

string TimeLog::str() const
{
  ostringstream oss;
  oss << start_.count() << endl;

  for ( const auto & point : points_ ) {
    oss << point.first << " " << point.second.count() << endl;
  }

  return oss.str();
}
