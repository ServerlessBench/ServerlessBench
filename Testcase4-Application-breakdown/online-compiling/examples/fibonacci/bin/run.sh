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

USAGE="$0 <N> <JOBS-COUNT>"

N=${1?$USAGE}
JOBS_COUNT=${2?$USAGE}

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR/../

printf "1. Clear workspace\n"
./bin/clear.sh

printf "2. Initialize gg\n"
gg init

printf "3. Create thunks for number %s\n" "$N"
./create-thunk.sh $N ./fib ./add

printf "4. Run calculation\n"
gg force --jobs=$JOBS_COUNT --engine=lambda "fib${N}_output"

printf "5. Result: %s\n" $(cat fib${N}_output)
