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

FUNCTION_NAME=gg_gcloud_function
FUNCTION_PATH=gcloud_function
REGION=us-central1
MEMORY=2048
TIMEOUT=300

cp common/{common,ggpaths}.py ${FUNCTION_PATH}
cp $(which gg-execute-static) ${FUNCTION_PATH}

gcloud beta functions deploy --region=${REGION} --memory ${MEMORY} ${FUNCTION_NAME} --trigger-http --quiet --runtime=python37 --source=${FUNCTION_PATH} --timeout=${TIMEOUT} --format=json --allow-unauthenticated --log-http --project=serverlessbench

rm ${FUNCTION_PATH}/{common,ggpaths}.py
rm ${FUNCTION_PATH}/gg-execute-static

echo
echo "export GG_GCLOUD_FUNCTION=[https-trigger-url]"
