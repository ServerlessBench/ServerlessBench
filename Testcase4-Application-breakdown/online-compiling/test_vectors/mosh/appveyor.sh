#!/bin/sh
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
#
# Cleanup for Appveyor peculiarities.
#

# Echo, eval, and error on shell commands.
eeval()
{
    echo "$0: $*" >&2
    eval "$@"
    rv=$?
    if [ $rv -ne 0 ]; then
	echo "$0: failed, exitcode $rv"
	exit $rv
    fi
    return 0
}

# We inherit a broken Windows path with a Windows Git.
PATH=/bin

# This supposedly fixes some failures.
exec 0</dev/null

# Mosh-specific environment
export LANG=en_US.UTF-8

case $1 in
    before_build)
	# This repo was checked out with Windows Git, repair it for Cygwin.
	eeval git config --local core.symlinks true
	eeval git clean --force --quiet -x -d
	eeval git reset --hard
	;;
    build_script)
	eeval ./autogen.sh
	eeval ./configure --enable-compile-warnings=error --enable-examples
	eeval make distcheck VERBOSE=1 V=1
	;;
    wait)
	touch wait.lck
	while [ -f wait.lck ]; do
	    sleep 10
	done
	;;
    *)
	echo "Fail: $0 $*"
	exit 2
	;;
esac
