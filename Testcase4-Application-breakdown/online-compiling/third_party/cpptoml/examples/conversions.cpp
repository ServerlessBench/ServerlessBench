//
// Copyright (c) 2020 Institution of Parallel and Distributed System, Shanghai Jiao Tong University
// ServerlessBench is licensed under the Mulan PSL v1.
// You can use this software according to the terms and conditions of the Mulan PSL v1.
// You may obtain a copy of Mulan PSL v1 at:
//     http://license.coscl.org.cn/MulanPSL
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
// PURPOSE.
// See the Mulan PSL v1 for more details.
//

#include <cstdint>
#include <iostream>

#include "cpptoml.h"

int main()
{
    auto root = cpptoml::make_table();

    root->insert("small-integer", int64_t{12});

    auto si = *root->get_as<int8_t>("small-integer");

    root->insert("small-integer2", si);

    try
    {
        root->insert("too-big", std::numeric_limits<uint64_t>::max());
    }
    catch (std::overflow_error&)
    {
    }

    root->insert("medium-integer", std::numeric_limits<int32_t>::max());

    try
    {
        root->get_as<int16_t>("medium-integer");
    }
    catch (std::overflow_error&)
    {
    }

    root->get_as<uint32_t>("medium-integer"); // signed as unsigned, checked

    root->insert("medium-negative", std::numeric_limits<int32_t>::min());

    try
    {
        root->get_as<int16_t>("medium-negative");
    }
    catch (std::underflow_error&)
    {
    }

    try
    {
        root->get_as<uint64_t>("medium-negative");
    }
    catch (std::underflow_error&)
    {
    }

    root->get_as<int64_t>("medium-negative");

    root->insert("float", 0.1f);
    root->get_as<double>("float");

    return 0;
}
