/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/serializer.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-02 16:34:47
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
// Copyright (C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __SERIALIZER__
#define __SERIALIZER__

#include <vector>
#include <iostream>
#include "Platform_Types.hpp"

class serializer {
public:
    serializer();
    virtual ~serializer();

    bool serialize(const uint8 _value);
    bool serialize(const uint16 _value);
    bool serialize(const uint32 _value);
    bool serialize(const uint8 *_data, uint32 _length);
    bool serialize(const std::vector<uint8> &_data);

    virtual const uint8 * get_data() const;
    virtual uint32 get_capacity() const;
    virtual uint32 get_size() const;

    virtual void set_data(uint8 *_data, uint32 _capacity);

    virtual void reset();

#ifdef VSOMEIP_DEBUGGING
    virtual void show();
#endif
private:
    std::vector<uint8> data_;
};
#endif 
