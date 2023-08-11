/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_handler.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-11 17:14:54
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "message_handler.hpp"

message_handler::message_handler() : message_handler_thread_m(std::bind(&message_handler::message_handler_thread,this)),
                                     action_cbk(std::bind(&message_handler::put_message_out,this,std::placeholders::_1))
{
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_LOGIN, login_m);
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_LOGOUT, logout_m);
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_CHECK, check_m);
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_FORWARD, forward_m);
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_BROADCAST, broadcast_m);
}

void message_handler::put_message(const message_impl& message)
{
    std::unique_lock<std::mutex> it_lock(message_deque_in_mutex);
    message_deque_in_m.push_back(message);
    message_deque_in_condition.notify_one();
}

void message_handler::put_message_out(const message_impl& message)
{
    std::lock_guard<std::mutex> it_lock(message_deque_out_mutex);
    message_deque_out_m.push_back(message);
}

boolean message_handler::pop_message(message_impl& mesg)
{
    std::lock_guard<std::mutex> it_lock(message_deque_out_mutex);
    if(!message_deque_out_m.empty())
    {
        message_m = message_deque_out_m.front();
        message_deque_out_m.pop_front();
        mesg = message_m;
        return true;
    }
    return false;
}

void message_handler::message_handle()
{
    static uint16 message_cnt = 0u;
    std::unique_lock<std::mutex> it_lock(message_deque_in_mutex);
    while(message_deque_in_m.empty())
    {
        spdlog::info("Message deque is empty waiting ....");
        message_deque_in_condition.wait(it_lock);
    }
    while(!message_deque_in_m.empty())
    {
        message_cnt++;
        auto message = message_deque_in_m.front();
        this->action(message.message_header_m.get_cmd_id(),message);
        message_deque_in_m.pop_front();
        #ifdef DEBUG
        spdlog::info("message action cnt[{}]",message_cnt);
        #endif
    }
}

void message_handler::message_handler_thread()
{
    std::cout << "message_handler_thread created" << std::endl;
    std::string threadName = "message_handler_thread";
    pthread_setname_np(pthread_self(), threadName.c_str());
    message_handler_thread_m.detach();
    while(1)
    {
        message_handle();
        // std::cout << "message_handler_thread" << std::endl;
    }
}


void LOGIN::Do_Action(message_impl& msg,MessageCallback mesgcbk)
{
    std::cout << "LOGIN action" << std::endl;
    message_impl resp_message;
    if(msg.message_header_m.get_topic_id() == (uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_REQ))
    {
       resp_message.message_header_m.set_header(MESSAGE_HEADER); 
       resp_message.message_header_m.set_topic_id((uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_ACK));
       resp_message.message_header_m.set_src_id((src_id_t)_IPC_ID_::_COM_SERVER_);
       resp_message.message_header_m.set_dst_id(msg.message_header_m.get_src_id());
       resp_message.message_header_m.set_cmd_id(_COM_CMD_TYPES_::COM_CMD_LOGIN);
       resp_message.message_header_m.set_len(0);
       resp_message.payload_m.push_back(0u);
       resp_message.payload_len_m  = 1u;
       mesgcbk(resp_message);
    }

}

void LOGOUT::Do_Action(message_impl& msg,MessageCallback mesgcbk)
{
    std::cout << "LOGOUT action" << std::endl;
}

void CHECK::Do_Action(message_impl& msg,MessageCallback mesgcbk)
{
    std::cout << "CHECK action" << std::endl;
}

void FORWARD::Do_Action(message_impl& msg,MessageCallback mesgcbk)
{
    std::cout << "FORWARD action" << std::endl;
}

void BROADCAST::Do_Action(message_impl& msg,MessageCallback mesgcbk)
{
    std::cout << "BROADCAST action" << std::endl;
}