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

#ifndef MANIFEST_HH
#define MANIFEST_HH

#include <vector>
#include <string>

class FileManifest
{
private:
  typedef std::string DummyDirectoryEntry;
  typedef std::pair<std::string, std::string> OutputTagEntry;

  std::vector<DummyDirectoryEntry> dummy_directories_ {};
  std::vector<OutputTagEntry> output_tags_ {};

public:
  FileManifest() {}

  void add_dummy_directory( const std::string & dummy_dir );
  void add_output_tag( const std::string & filename, const std::string & tag );

  std::string serialize() const;
};

#endif /* MANIFEST_HH */
