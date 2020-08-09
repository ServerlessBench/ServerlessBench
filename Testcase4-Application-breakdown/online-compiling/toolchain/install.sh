#!/bin/bash -xe
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

SRCDIR=`pwd`
DESTDIR=${SRCDIR}/bin
INSTDIR=${SRCDIR}/inst/usr/bin
GCC_INSTDIR=${SRCDIR}/inst/usr/libexec/gcc/x86_64-linux-gnu/7

mkdir -p ${DESTDIR}

for exe in g++ gcc ld as ar ranlib nm strip as readelf
do
  cp ${INSTDIR}/gg-${exe} ${DESTDIR}/${exe}
done

for exe in cc1 cc1plus collect2
do
  cp ${GCC_INSTDIR}/${exe} ${DESTDIR}/${exe}
done

for exe in $(ls ${DESTDIR})
do
  strip ${DESTDIR}/${exe}
done
