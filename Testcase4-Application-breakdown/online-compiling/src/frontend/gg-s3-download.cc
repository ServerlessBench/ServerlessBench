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
#include "thunk/ggutils.hh"
#include "util/path.hh"

using namespace std;

void usage( const char * argv0 )
{
  cerr << argv0 << " S3-REGION S3-BUCKET [S3-ENDPOINT]" << endl;
}

int main( int argc, char * const argv[] )
{
  if ( argc <= 0 ) {
    abort();
  }

  if ( argc < 3 ) {
    usage( argv[ 0 ] );
    return EXIT_FAILURE;
  }

  string s3_region { argv[ 1 ] };
  string s3_bucket { argv[ 2 ] };
  string s3_endpoint;

  if ( argc == 4 ) {
    s3_endpoint = argv[ 3 ];
  }

  vector<storage::GetRequest> files;

  string object_key;
  while ( cin >> object_key ) {
    files.push_back( { object_key, gg::paths::blob( object_key ) } );
  }

  S3ClientConfig client_config;
  client_config.region = s3_region;

  S3Client s3_client { {}, client_config };
  s3_client.download_files( s3_bucket, files );

  return EXIT_SUCCESS;
}
