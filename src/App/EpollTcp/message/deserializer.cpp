// Copyright (C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cstring>
#include "deserializer.hpp"
#include "byte_order.hpp"
#include "spdlog/spdlog.h"
deserializer::deserializer()
    : position_(data_.begin()),
      remaining_(0)
{
}

deserializer::deserializer(uint8 *_data, uint32 _length)
    : data_(_data, _data + _length),
      position_(data_.begin()),
      remaining_(_length)
{

}

deserializer::deserializer(const deserializer &_other)
    : data_(_other.data_),
      position_(_other.position_),
      remaining_(_other.remaining_)
{
}

deserializer::~deserializer() {
}

uint32 deserializer::get_available() const {
    return data_.size();
}

uint32 deserializer::get_remaining() const {
    return remaining_;
}

void deserializer::set_remaining(uint32 _remaining) {
    remaining_ = _remaining;
}

bool deserializer::deserialize(uint8& _value) {
    if (0 == remaining_)
    {
        spdlog::error("deserialize fail because of _length[{:d}] == remaining_[{:d}] [{}] line[{}]",0,remaining_,__FUNCTION__,__LINE__);
        return false;
    }
        

    _value = *position_++;

    remaining_--;
    return true;
}

bool deserializer::deserialize(uint16& _value) {
    if (2 > remaining_)
    {
        spdlog::error("deserialize fail because of _length[{:d}] > remaining_[{:d}] [{}] line[{}]",2,remaining_,__FUNCTION__,__LINE__);
        return false;
    }
        

    uint8 byte0, byte1;
    byte0 = *position_++;
    byte1 = *position_++;
    remaining_ -= 2;

    _value = BYTES_TO_WORD(byte0, byte1);

    return true;
}

bool deserializer::deserialize(uint32 &_value) {
    if (4 > remaining_)
    {
        spdlog::error("deserialize fail because of _length[{:d}] > remaining_[{:d}] [{}] line[{}]",4,remaining_,__FUNCTION__,__LINE__);
        return false;
    }
        

    uint8 byte0 = 0, byte1, byte2, byte3;
    byte0 = *position_++;
    byte1 = *position_++;
    byte2 = *position_++;
    byte3 = *position_++;
    remaining_ -= 4;

    _value = BYTES_TO_LONG(
            byte0, byte1, byte2, byte3);

    return true;
}

bool deserializer::deserialize(uint8 *_data, uint32 _length) {
    if (_length > remaining_)
    {
        spdlog::error("deserialize fail because of _length[{:d}] > remaining_[{:d}] [{}] line[{}]",_length,remaining_,__FUNCTION__,__LINE__);
        return false;
    }
        
    if (_data == nullptr)
    {
        spdlog::error("deserialize fail because of nullptr [{}] line[{}]",__FUNCTION__,__LINE__);
        return false;
    }
    
    std::memcpy(_data, &data_[static_cast<std::vector<uint8>::size_type>(position_ - data_.begin())], _length);
    position_ += static_cast<std::vector<uint8>::difference_type>(_length);
    remaining_ -= _length;

    return true;
}

bool deserializer::deserialize(std::string& _target, uint32 _length) {
    if (_length > remaining_ || _length > _target.capacity()) {
        return false;
    }
    _target.assign(position_, position_ + _length);
    position_ += _length;
    remaining_ -= _length;

    return true;
}

bool deserializer::deserialize(std::vector< uint8 >& _value) {
    if (_value.capacity() > remaining_)
        return false;

    _value.assign(position_, position_
            + static_cast<std::vector<uint8>::difference_type>(_value.capacity()));
    position_ += static_cast<std::vector<uint8>::difference_type>(_value.capacity());
    remaining_ -= _value.capacity();

    return true;
}

bool deserializer::look_ahead(uint32 _index, uint8 &_value) const {
    if (_index >= data_.size())
        return false;

    _value = *(position_ + static_cast<std::vector<uint8>::difference_type>(_index));

    return true;
}

bool deserializer::look_ahead(uint32 _index, uint16 &_value) const {
    if (_index+1 >= data_.size())
        return false;

    std::vector< uint8 >::iterator i = position_ +
            static_cast<std::vector<uint8>::difference_type>(_index);
    _value = BYTES_TO_WORD(*i, *(i+1));

    return true;
}

bool deserializer::look_ahead(uint32 _index, uint32 &_value) const {
    if (_index+3 >= data_.size())
        return false;

    std::vector< uint8 >::const_iterator i = position_ + static_cast<std::vector<uint8>::difference_type>(_index);
    _value = BYTES_TO_LONG(*i, *(i+1), *(i+2), *(i+3));

    return true;
}

void deserializer::set_data(const uint8 *_data,  uint32 _length) 
{
    if (0 != _data) {
        data_.assign(_data, _data + _length);
        position_ = data_.begin();
        remaining_ = static_cast<std::vector<uint8>::size_type>(data_.end() - position_);
    } else {
        data_.clear();
        position_ = data_.end();
        remaining_ = 0;
    }
}

void deserializer::append_data(const uint8 *_data, uint32 _length) {
    std::vector<uint8>::difference_type offset = (position_ - data_.begin());
    data_.insert(data_.end(), _data, _data + _length);
    position_ = data_.begin() + offset;
    remaining_ += _length;
}

void deserializer::drop_data(uint32 _length) {
    if (position_ + static_cast<std::vector<uint8>::difference_type>(_length) < data_.end())
        position_ += static_cast<std::vector<uint8>::difference_type>(_length);
    else
        position_ = data_.end();
}

void deserializer::reset() 
{
    data_.clear();
    position_ = data_.begin();
    remaining_ = data_.size();
}

#ifdef DEBUGGING
void deserializer::show() const {
    std::stringstream its_message;
    its_message << "("
            << std::hex << std::setw(2) << std::setfill('0')
            << (int)*position_ << ", "
            << std:: dec << remaining_ << ") ";
    for (int i = 0; i < data_.size(); ++i)
        its_message << std::hex << std::setw(2) << std::setfill('0')
                    << (int)data_[i] << " ";
    INFO << its_message;
}
#endif

