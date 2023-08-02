/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message_header.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-02 17:27:07
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __MESSAGE_HEADER__
#define __MESSAGE_HEADER__
#include "Platform_Types.hpp"
#include "Message_Cfg.hpp"
#include "serializer.hpp"
#include "deserializer.hpp"

enum class _COM_CMD_TYPES_
{
    COM_CMD_LOGIN = 1,
    COM_CMD_LOGOUT,   
    COM_CMD_CHECK,      /*get connected to COM server tasks type*/ 
    COM_CMD_FORWARD,    /*forward srcTask data to destTask*/     
    COM_CMD_BROADCAST,   /*broadcast srcTask data to every tasks*/  
    COM_CMD_MAX,
    COM_CMD_UNKNOWN = 255, /*unknown*/
};

class message_header
{
public:
    message_header();
    message_header(const message_header& _header);

    ~message_header();

    boolean serialize(serializer *_to) const;
    boolean deserialize(deserializer *_from);


public:
    header_t header ;
    src_id_t src_id;              /*Source identity*/
    dst_id_t dst_id;              /*Destination id*/
    topic_id_t topic_id;            /*topic identity*/
    _COM_CMD_TYPES_ cmd_id;     /*com identity*/
    len_t len;                 /*remain len without header*/
};

#endif