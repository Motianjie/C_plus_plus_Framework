/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message_impl.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-03 15:16:06
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
    message_impl(const message_header& header_,const uint32 payload_len,const uint8* payload);
    ~message_impl();
    /**
     * @description: 进程间通信消息体payload序列化
     * @param {shared_ptr<serializer>} _to 序列化器
     * @return {true: serialize success, false: serialize failure}
     */
    boolean serialize(std::shared_ptr<serializer> _to) const;
    /**
     * @description: 进程间通信消息体payload反序列化
     * @param {shared_ptr<serializer>} _from 反序列化器
     * @return {true: deserialize success, false: deserialize failure}
     */
    boolean deserialize(std::shared_ptr<deserializer> _from);

public:
    message_header message_header_m; //进程间通信消息头
    uint32 payload_len_m;   //进程间通信payload长度
    std::vector<uint8> payload_m;//进程间通信payload
};

#endif