#!/usr/bin/perl
#
# Copyright (c) 2020 Institution of Parallel and Distributed System, Shanghai Jiao Tong University
# ServerlessBench is licensed under the Mulan PSL v1.
# You can use this software according to the terms and conditions of the Mulan PSL v1.
# You may obtain a copy of Mulan PSL v1 at:
#     http://license.coscl.org.cn/MulanPSL
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
# PURPOSE.
# See the Mulan PSL v1 for more details.
#

use strict;
use warnings;
use MIME::Base64;

my @vectors = (
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff",
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff",
    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00",
    "\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa",
    "\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\x55\x55\x55\x55\x55\x55\x55\x55",
    "\x55\x55\x55\x55\x55\x55\x55\x55\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa",
    "\x01\x02\x04\x08\x10\x20\x40\x80\xfe\xfd\xfb\xf7\xef\xdf\xbf\x7f",
    );

print 'base64_test_row static_base64_vector[] = {' . "\n";
for my $v (@vectors) {
    print '    { "';
    my @chars = split '', $v;
    for my $c (@chars) {
	printf "\\x%02x", ord($c);
    }
    print '", "' . encode_base64($v, "") . '" },' . "\n";
}
print '    { "", "" }' . "\n";
print "};\n";
