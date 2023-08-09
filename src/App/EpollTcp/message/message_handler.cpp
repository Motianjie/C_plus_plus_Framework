/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_handler.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-04 17:10:02
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "message_handler.hpp"

message_handler::message_handler() : message_handler_thread_m(std::bind(&message_handler::message_handler_thread,this))
{
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_LOGIN, login_m);
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_LOGOUT, logout_m);
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_CHECK, check_m);
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_FORWARD, forward_m);
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_BROADCAST, broadcast_m);
}

void message_handler::put_message(const message_impl& message)
{
    std::unique_lock<std::mutex> it_lock(message_deque_mutex);
    message_deque_m.push_back(message);
    message_deque_condition.notify_one();
}

void message_handler::message_handle()
{
    static uint16 message_cnt = 0u;
    std::unique_lock<std::mutex> it_lock(message_deque_mutex);
    while(message_deque_m.empty())
    {
        spdlog::info("Message deque is empty waiting ....");
        message_deque_condition.wait(it_lock);
    }
    while(!message_deque_m.empty())
    {
        message_cnt++;
        auto message = message_deque_m.front();
        this->action(message.message_header_m.get_cmd_id());
        message_deque_m.pop_front();
        spdlog::info("message action cnt[{}]",message_cnt);
    }
}

void message_handler::message_handler_thread()
{
    std::cout << "message_handler_thread created" << std::endl;
    std::string threadName = "message_handler_thread";
    pthread_setname_np(pthread_self(), threadName.c_str());
    // message_handler_thread_m.detach();
    while(1)
    {
        message_handle();
        std::cout << "message_handler_thread" << std::endl;
    }
}


void LOGIN::Do_Action()
{
    std::cout << "LOGIN action" << std::endl;
}

void LOGOUT::Do_Action()
{
    std::cout << "LOGOUT action" << std::endl;
}

void CHECK::Do_Action()
{
    std::cout << "CHECK action" << std::endl;
}

void FORWARD::Do_Action()
{
    std::cout << "FORWARD action" << std::endl;
}

void BROADCAST::Do_Action()
{
    std::cout << "BROADCAST action" << std::endl;
}