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

/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#ifndef MODELS_TIMEOUTS_HH
#define MODELS_TIMEOUTS_HH

#include <chrono>

static constexpr std::chrono::milliseconds NO_TIMEOUT             { 0 };
static constexpr std::chrono::milliseconds VERY_SHORT_TIMEOUT { 5'000 };
static constexpr std::chrono::milliseconds SHORT_TIMEOUT      { 7'500 };
static constexpr std::chrono::milliseconds LONG_TIMEOUT      { 12'500 };
static constexpr std::chrono::milliseconds VERY_LONG_TIMEOUT { 17'500 };

static constexpr std::chrono::milliseconds DEPGEN_TIMEOUT     = VERY_LONG_TIMEOUT;
static constexpr std::chrono::milliseconds PREPROCESS_TIMEOUT = LONG_TIMEOUT;
static constexpr std::chrono::milliseconds COMPILE_TIMEOUT    = SHORT_TIMEOUT;
static constexpr std::chrono::milliseconds ASSEMBLE_TIMEOUT   = SHORT_TIMEOUT;
static constexpr std::chrono::milliseconds LINK_TIMEOUT       = VERY_SHORT_TIMEOUT;
static constexpr std::chrono::milliseconds AR_TIMEOUT         = VERY_SHORT_TIMEOUT;
static constexpr std::chrono::milliseconds STRIP_TIMEOUT      = VERY_SHORT_TIMEOUT;
static constexpr std::chrono::milliseconds RANLIB_TIMEOUT     = VERY_SHORT_TIMEOUT;

#endif /* MODELS_TIMEOUTS_HH */
