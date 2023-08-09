/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/deserializer.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-02 19:28:51
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
// Copyright (C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __DESERIALIZER__
#define __DESERIALIZER__

#include <iostream>
#include <vector>
#include <string>
#include "Platform_Types.hpp"


class message_impl;

class deserializer {
public:
     deserializer();
     deserializer(uint8 *_data, uint32 _length);
     deserializer(const deserializer& _other);
     virtual ~deserializer();

     void set_data(const uint8 *_data, uint32 _length);
     void append_data(const uint8 *_data, uint32 _length);
     void drop_data(uint32 _length);

     uint32 get_available() const;
     uint32 get_remaining() const;
     void set_remaining(uint32 _remaining);

    // to be used by applications to deserialize a message
     message_impl *deserialize_message();

    // to be used (internally) by objects to deserialize their members
    // Note: this needs to be encapsulated!
     bool deserialize(uint8& _value);
     bool deserialize(uint16& _value);
     bool deserialize(uint32& _value);
     bool deserialize(uint8 *_data, uint32 _length);
     bool deserialize(std::string& _target, uint32 _length);
     bool deserialize(std::vector<uint8>& _value);

     bool look_ahead(uint32 _index, uint8 &_value) const;
     bool look_ahead(uint32 _index, uint16 &_value) const;
     bool look_ahead(uint32 _index, uint32 &_value) const;

     void reset();

#ifdef DEBUGGING
     void show() const;
#endif
public:
    std::vector<uint8> data_;
    std::vector<uint8>::iterator position_;
    uint32 remaining_;

};

#endif
