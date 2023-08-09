/*
 * @FilePath: /C_plus_plus_Framework/src/App/utility/byte_order.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-02 16:25:35
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
// Copyright (C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __BYTE_ORDER_
#define __BYTE_ORDER_

#include <endian.h>
#include "Platform_Types.hpp"

#if __BYTE_ORDER == __LITTLE_ENDIAN

#define BYTES_TO_WORD(x0, x1) (uint16((x0) << 8 | (x1)))
#define BYTES_TO_LONG(x0, x1, x2, x3) (uint32((x0) << 24 | (x1) << 16 | (x2) << 8 | (x3)))

#define WORDS_TO_LONG(x0, x1) (uint32((x0) << 16 | (x1)))

#define WORD_BYTE0(x) (uint8((x) & 0xFF))
#define WORD_BYTE1(x) (uint8((x) >> 8))

#define LONG_BYTE0(x) (uint8((x) & 0xFF))
#define LONG_BYTE1(x) (uint8(((x) >> 8) & 0xFF))
#define LONG_BYTE2(x) (uint8(((x) >> 16) & 0xFF))
#define LONG_BYTE3(x) (uint8(((x) >> 24) & 0xFF))

#define LONG_WORD0(x) (uint16((x) & 0xFFFF))
#define LONG_WORD1(x) (uint16(((x) >> 16) & 0xFFFF))

#elif __BYTE_ORDER == __BIG_ENDIAN

#define BYTES_TO_WORD(x0, x1) (uint16((x1) << 8 | (x0)))
#define BYTES_TO_LONG(x0, x1, x2, x3) (uint32((x3) << 24 | (x2) << 16 | (x1) << 8 | (x0)))

#define WORDS_TO_LONG(x0, x1) (uint32((x1) << 16 | (x0)))

#define WORD_BYTE0(x) (uint8((x) >> 8))
#define WORD_BYTE1(x) (uint8((x) & 0xFF))

#define LONG_BYTE0(x) (uint8(((x) >> 24) & 0xFF))
#define LONG_BYTE1(x) (uint8(((x) >> 16) & 0xFF))
#define LONG_BYTE2(x) (uint8(((x) >> 8) & 0xFF))
#define LONG_BYTE3(x) (uint8((x) & 0xFF))

#define LONG_WORD0(x) (uint16(((x) >> 16) & 0xFFFF))
#define LONG_WORD1(x) (uint16((x) & 0xFFFF))

#else


#endif

#endif
