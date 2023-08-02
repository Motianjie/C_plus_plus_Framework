/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/serializer.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-02 16:34:31
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
// Copyright (C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

//#include <cstring>
#include "serializer.hpp"
#include "byte_order.hpp"

serializer::serializer() :data_(0) 
{
}

serializer::~serializer() 
{
}


bool serializer::serialize(const uint8 _value) 
{
    data_.push_back(_value);
    return true;
}

bool serializer::serialize(const uint16 _value) 
{
    data_.push_back(WORD_BYTE1(_value));
    data_.push_back(WORD_BYTE0(_value));
    return true;
}

bool serializer::serialize(const uint32 _value) 
{
    data_.push_back(LONG_BYTE3(_value));
    data_.push_back(LONG_BYTE2(_value));
    data_.push_back(LONG_BYTE1(_value));
    data_.push_back(LONG_BYTE0(_value));
    return true;
}

bool serializer::serialize(const uint8 *_data, uint32 _length) {
    try {
        data_.insert(data_.end(), _data, _data + _length);
    } catch(const std::bad_alloc &e) {
        
        return false;
    }
    return true;
}

bool serializer::serialize(const std::vector<uint8> &_data) {
    try {
        data_.insert(data_.end(),_data.begin(), _data.end());
    } catch(const std::bad_alloc &e) {
        std::cout << "Couldn't allocate memory in serializer::serialize(vector)" << e.what();
        return false;
    }
    return true;
}

const uint8 * serializer::get_data() const {
    return data_.data();
}

uint32_t serializer::get_capacity() const {
    return static_cast<std::uint32_t>(data_.max_size());
}

uint32_t serializer::get_size() const {
    return static_cast<std::uint32_t>(data_.size());
}

void serializer::set_data(uint8 *_data, uint32_t _capacity) {
    data_.clear();
    try {
        data_.insert(data_.end(), _data, _data + _capacity);
    } catch(const std::bad_alloc &e) {
        std::cout << "Couldn't allocate memory in serializer::set_data" << e.what();
    }
}

void serializer::reset() 
{
    data_.clear();
}

#ifdef DEBUGGING
void serializer::show() {
    std::stringstream its_data;
    its_data << "SERIALIZED: ";
    for (const uint8& e : data_)
        its_data << std::setw(2) << std::setfill('0')
                 << std::hex << (int)e;
    INFO << its_data.str();
}
#endif
