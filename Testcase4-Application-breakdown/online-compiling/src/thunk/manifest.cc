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

#include "manifest.hh"

#include <sstream>

using namespace std;

void FileManifest::add_dummy_directory( const string & dummy_dir )
{
  dummy_directories_.emplace_back( dummy_dir );
}

void FileManifest::add_output_tag( const string & filename, const string & tag )
{
  output_tags_.emplace_back( filename, tag );
}

string FileManifest::serialize() const
{
  ostringstream sout;

  for ( const auto & entry : dummy_directories_ ) {
    sout << "D" << '\0' << entry << '\0';
  }

  for ( const auto & entry : output_tags_ ) {
    sout << "O" << '\0' << entry.first << '\0' << entry.second << '\0';
  }

  return sout.str();
}
