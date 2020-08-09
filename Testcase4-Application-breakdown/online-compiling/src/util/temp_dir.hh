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

#ifndef TEMP_DIR_HH
#define TEMP_DIR_HH

#include <vector>
#include <string>

class UniqueDirectory
{
private:
  std::vector<char> mutable_temp_dirname_;

protected:
  bool moved_away_;

public:
  UniqueDirectory( const std::string & dirname_template );
  virtual ~UniqueDirectory() {}

  std::string name( void ) const;

  /* ban copying */
  UniqueDirectory( const UniqueDirectory & other ) = delete;
  UniqueDirectory & operator=( const UniqueDirectory & other ) = delete;

  /* allow move constructor */
  UniqueDirectory( UniqueDirectory && other );

  /* ... but not move assignment operator */
  UniqueDirectory & operator=( UniqueDirectory && other ) = delete;
};

/* TempDirectory is deleted when object destroyed */
class TempDirectory : public UniqueDirectory
{
public:
  using UniqueDirectory::UniqueDirectory;

  /* allow move constructor */
  TempDirectory( TempDirectory && other ) : UniqueDirectory( std::move( other ) ) {}

  ~TempDirectory();
};

#endif /* TEMP_DIR_HH */
