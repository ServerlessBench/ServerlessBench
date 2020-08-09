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

USAGE="$0 <N> <FIB-PATH> <ADD-PATH>"

N=${1?$USAGE}
FIB_PATH=${2?$USAGE}
ADD_PATH=${3?$USAGE}

FIB_HASH=$(gg-hash $FIB_PATH)
ADD_HASH=$(gg-hash $ADD_PATH)

gg-create-thunk --envar FIB_FUNCTION_HASH=${FIB_HASH} \
                --envar ADD_FUNCTION_HASH=${ADD_HASH} \
                --executable ${FIB_HASH} \
                --executable ${ADD_HASH} \
                --output out \
                --output left \
                --output right \
                --placeholder fib${N}_output \
                ${FIB_HASH} fib ${N}

gg-collect $FIB_PATH $ADD_PATH
