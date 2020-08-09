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

/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include "strict_conversions.hh"
#include "util/exception.hh"

using namespace std;

long int strict_atoi( const string & str, const int base )
{
    if ( str.empty() ) {
        throw runtime_error( "Invalid integer string: empty" );
    }

    char *end;

    errno = 0;
    long int ret = strtol( str.c_str(), &end, base );

    if ( errno != 0 ) {
        throw unix_error( "strtol" );
    } else if ( end != str.c_str() + str.size() ) {
        throw runtime_error( "Invalid integer: " + str );
    }

    return ret;
}

double strict_atof( const string & str )
{
    if ( str.empty() ) {
        throw runtime_error( "Invalid floating-point string: empty" );
    }

    char *end;

    errno = 0;
    double ret = strtod( str.c_str(), &end );

    if ( errno != 0 ) {
        throw unix_error( "strtod" );
    } else if ( end != str.c_str() + str.size() ) {
        throw runtime_error( "Invalid floating-point number: " + str );
    }

    return ret;
}
