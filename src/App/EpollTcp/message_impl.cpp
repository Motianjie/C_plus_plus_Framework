/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message_impl.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-03 10:58:41
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "message_impl.hpp"

message_impl::message_impl() :  len_m(0u),
                                data_m(0u) 
{
}

message_impl::~message_impl()
{}


boolean message_impl::serialize(std::shared_ptr<serializer> _to)const
{
    return (0 != _to && 
           _to->serialize((uint32)this->data_m.size()) &&
           _to->serialize(this->data_m.data(), this->data_m.size()));
}

boolean message_impl::deserialize(std::shared_ptr<deserializer> _from)
{
    bool is_successful = true;


        // 0 != _from
        // && _from->deserialize(this->message_header_m.header)
        // && _from->deserialize(this->message_header_m.src_id)
        // && _from->deserialize(this->message_header_m.dst_id)
        // && _from->deserialize(this->message_header_m.topic_id)
        // && _from->deserialize((uint32&)this->message_header_m.cmd_id)
        // && _from->deserialize(this->message_header_m.len)
        // && _from->deserialize(this->len_m)
    _from->deserialize(this->message_header_m.header);
    _from->deserialize(this->message_header_m.src_id);
    _from->deserialize(this->message_header_m.dst_id);
    _from->deserialize(this->message_header_m.topic_id);
    _from->deserialize((uint32&)this->message_header_m.cmd_id);
    _from->deserialize(this->message_header_m.len);
    _from->deserialize(this->len_m);
    this->data_m.resize(this->len_m);//需要分配空间，不然data_m.data()是空指针，下方memcpy导致越界
    is_successful = _from->deserialize(data_m.data(),this->len_m);
    return is_successful;


}