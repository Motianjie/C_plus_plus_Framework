/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_action_base.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-17 14:08:31
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "message_action_base.hpp"

void LOGIN::Do_Action(message_impl& msg)
{
    std::cout << "LOGIN action" << std::endl;
    //回复LOGIN ACK给客户端
    message_impl resp_message;
    if(msg.message_header_m.get_topic_id() == (uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_REQ))
    {
       resp_message.message_header_m.set_header(MESSAGE_HEADER); 
       resp_message.message_header_m.set_cnt(msg.message_header_m.get_cnt());
       resp_message.message_header_m.set_topic_id((uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_ACK));
       resp_message.message_header_m.set_src_id((src_id_t)_IPC_ID_::_COM_SERVER_);
       resp_message.message_header_m.set_dst_id(msg.message_header_m.get_src_id());
       resp_message.message_header_m.set_cmd_id(_COM_CMD_TYPES_::COM_CMD_LOGIN);
       resp_message.message_header_m.set_len(0);
       resp_message.payload_m.push_back(0u);
       resp_message.payload_len_m  = 1u;
       if(message_handler_m.get())
        message_handler_m->put_message_out(resp_message);
       else
        spdlog::error("login message handler null put message out failed");
    }

}

void LOGOUT::Do_Action(message_impl& msg)
{
    std::cout << "LOGOUT action" << std::endl;
}

void CHECK::Do_Action(message_impl& msg)
{
    std::cout << "CHECK action" << std::endl;
}

void FORWARD::Do_Action(message_impl& msg)
{
    std::cout << "FORWARD action" << std::endl;
    //原封不动
    if(message_handler_m.get())
        message_handler_m->put_message_out(msg);
    else
        spdlog::error("login message handler null put message out failed");
}

void BROADCAST::Do_Action(message_impl& msg)
{
    std::cout << "BROADCAST action" << std::endl;
}