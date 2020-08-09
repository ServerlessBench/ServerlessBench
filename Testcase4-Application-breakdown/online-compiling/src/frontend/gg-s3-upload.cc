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

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

#include "net/s3.hh"

using namespace std;

int main()
{
  vector<storage::PutRequest> files;

  string filename;
  while ( cin >> filename ) {
    files.push_back( { filename, roost::rbasename( filename ).string(), "" } );
  }

  S3Client s3_client { {} };
  s3_client.upload_files( "ggfunbucket", files,
    [] ( const storage::PutRequest & request )
    {
      cout << "Upload done: " + request.filename.string() + "\n";
    }
  );

  return EXIT_SUCCESS;
}
