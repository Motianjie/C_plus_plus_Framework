/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_impl.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-11 17:07:56
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "message_impl.hpp"
#include <cstring>

message_impl::message_impl() :  payload_len_m(0u),
                                payload_m(0u) 
{
}

message_impl::message_impl(const message_header& header_,const uint32 payload_len,const uint8* payload)
{
    std::memcpy(&message_header_m,&header_,sizeof(message_header));
    payload_len_m = payload_len;
    try
    {
        payload_m.insert(payload_m.end(), payload, payload + payload_len);
    }catch(const std::bad_alloc& e)
    {
        std::cout << "bad alloc" << e.what() << std::endl;
    }
}

message_impl::~message_impl()
{
}


boolean message_impl::serialize(std::shared_ptr<serializer> _to)const
{
    return (0 != _to && 
           _to->serialize((uint32)this->payload_m.size()) &&
           _to->serialize(this->payload_m.data(), this->payload_m.size()));
}

boolean message_impl::deserialize(std::shared_ptr<deserializer> _from)
{
    bool is_successful;
    if(0 != _from)
        is_successful = _from->deserialize(this->payload_len_m);
    if(is_successful)
    {
        this->payload_m.resize(this->payload_len_m);//需要分配空间，不然data_m.data()是空指针，下方memcpy导致访问空指针
        is_successful = _from->deserialize(payload_m.data(),this->payload_len_m);
    }
    return is_successful;
}

void message_impl::show_message() const
{
#ifdef DEBUG  
    spdlog::info("show Recv message payload_len[{}] payload elements:{}",payload_len_m,spdlog::to_hex(payload_m));
#endif
}