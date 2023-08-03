/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message_impl.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-03 10:57:59
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __MESSAGE_IMPL__
#define __MESSAGE_IMPL__


#include "Message_Cfg.hpp"
#include "message_header.hpp"

class message_impl
{
public:
    message_impl();

    ~message_impl();

    boolean serialize(std::shared_ptr<serializer> _to) const;
    boolean deserialize(std::shared_ptr<deserializer> _from);

public:
    message_header message_header_m;
    uint32 len_m;
    std::vector<uint8> data_m;

};

#endif