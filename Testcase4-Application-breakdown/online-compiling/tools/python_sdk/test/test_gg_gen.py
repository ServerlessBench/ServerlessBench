#!/usr/bin/env python3

# Copyright (c) 2020 Institution of Parallel and Distributed System, Shanghai Jiao Tong University
# ServerlessBench is licensed under the Mulan PSL v1.
# You can use this software according to the terms and conditions of the Mulan PSL v1.
# You may obtain a copy of Mulan PSL v1 at:
#     http://license.coscl.org.cn/MulanPSL
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
# PURPOSE.
# See the Mulan PSL v1 for more details.


from gg_sdk import GG, GGThunk

test_prog_bin = 'test_program'
test_lines = 'test_lines.txt'
num_test_lines = 10

def main():
    gg = GG()
    all_thunks = []
    for i in range(num_test_lines):
        next_thunk = GGThunk(exe=test_prog_bin, outname='test_%d.out' % i,
                exe_args=[test_lines, '%d' % i], args_infiles=False)
        next_thunk.add_infile(test_lines)
        all_thunks.append(next_thunk)

    gg.create_thunks(all_thunks)

if __name__ == '__main__':
    main()
