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

USAGE="$0 <JOBS-COUNT>"

JOBS_COUNT=${1?$USAGE}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR/../

printf "1. Generate Makefile\n"
./gen_makefile.py 0 6 16 1 > Makefile

printf "2. Initialize gg\n"
rm -rf .gg
gg init

printf "3. Execute 'make' to create thunks\n"
gg-infer make -j$(nproc)

printf "4. Run video processing jobs\n"
gg force --jobs=$JOBS_COUNT --engine=lambda *.ivf

printf "5. Build output.avi\n"
ls *-vpxenc.ivf | while read each; do echo "file '$each'" >> mylist.txt; done
ffmpeg -f concat -i mylist.txt -codec copy output.avi

printf "6. Result:\n"
file output.avi
