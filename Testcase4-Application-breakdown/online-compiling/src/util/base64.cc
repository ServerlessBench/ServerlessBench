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

#include "base64.hh"

#include <crypto++/sha.h>
#include <crypto++/hex.h>
#include <crypto++/base64.h>

using namespace CryptoPP;
using namespace std;

string base64::encode( const string & input )
{
  SHA256 hash_function;
  string ret;

  /* Each stage of the Crypto++ pipeline will delete the pointer it owns
     (https://www.cryptopp.com/wiki/Pipelining) */

  StringSource s( input, true,
                  new Base64Encoder( new StringSink( ret ) ) );

  return ret;
}

string base64::decode( const string & input )
{
  SHA256 hash_function;
  string ret;

  /* Each stage of the Crypto++ pipeline will delete the pointer it owns
     (https://www.cryptopp.com/wiki/Pipelining) */

  StringSource s( input, true,
                  new Base64Decoder( new StringSink( ret ) ) );

  return ret;
}
