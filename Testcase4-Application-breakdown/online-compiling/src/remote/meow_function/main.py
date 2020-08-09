#!/usr/bin/env python3.6

# Copyright (c) 2020 Institution of Parallel and Distributed System, Shanghai Jiao Tong University
# ServerlessBench is licensed under the Mulan PSL v1.
# You can use this software according to the terms and conditions of the Mulan PSL v1.
# You may obtain a copy of Mulan PSL v1 at:
#     http://license.coscl.org.cn/MulanPSL
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
# PURPOSE.
# See the Mulan PSL v1 for more details.


import os
import sys
import time
import shutil
import subprocess as sub
from base64 import b64decode, b64encode

# Set up environment variables necessary
curdir = os.path.dirname(__file__)
sys.path.append(curdir)
sys.path.append(os.path.join(curdir, 'packages'))
os.environ['PATH'] = "{}:{}".format(curdir, os.environ.get('PATH', ''))

if not os.environ.get('GG_DIR'):
    os.environ['GG_DIR'] = "/tmp/_gg"

if not os.environ.get('GG_CACHE_DIR'):
    os.environ['GG_CACHE_DIR'] = "/tmp/_gg/_cache"

# Now we can import gg stuff...
from common import run_command

def handler(event, context):
    os.environ['GG_STORAGE_URI'] = event['storageBackend']
    coordinator_address = event['coordinator']
    coordinator_host, coordinator_port = event['coordinator'].split(':')

    if event.get('timelog'):
        os.environ['GG_EXECUTE_TIMELOG'] = '1'

    return_code, stdout = run_command(["gg-meow-worker",
        coordinator_host, coordinator_port])

    print(stdout)
    print(return_code)

    return {
        'returnCode': return_code,
        'stdout': stdout,
    }
