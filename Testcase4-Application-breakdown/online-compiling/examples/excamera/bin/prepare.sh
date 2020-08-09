#!/bin/bash -e
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

USAGE="$0 <AVI-PATH>"

AVI_PATH="$(readlink -f ${1?$USAGE})"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR/../

# delete prev chunks
./bin/clear.sh

# build from avi source
ffmpeg -i $AVI_PATH -pix_fmt yuv420p input.y4m
ffmpeg -i input.y4m -f segment -segment_time 1 -pix_fmt yuv420p 0000%4d.y4m
