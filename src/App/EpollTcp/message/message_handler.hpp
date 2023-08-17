/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_handler.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-17 15:28:29
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __message_handler__
#define __message_handler__

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <deque>
#include <functional>
#include "Message_Cfg.hpp"
#include "spdlog/spdlog.h"
#include "message_header.hpp"
#include "message_impl.hpp"
#include "routing_manager.hpp"
#include "message_handler.hpp"
#include "routing_tables.hpp"
#include "message_action_impl.hpp"

class message_impl;
class routing_tables;
class message_handler;
class message_action_impl;

class message_handler : public std::enable_shared_from_this<message_handler>
{
public:
    message_handler(const std::shared_ptr<routing_tables>& _routing_tables);
    
    ~message_handler()
    {
        std::cout << "message_handler deconstructed" << std::endl;
        // message_handler_thread_m.join();   
    }

    void put_message(const message_impl& message);
    void put_message_out(const message_impl& message);
    void message_handle();
    void message_handler_thread();

    boolean pop_message(message_impl& mesg);

private:
    std::shared_ptr<routing_tables> routing_tables_m;   
    std::shared_ptr<message_action_impl> message_action_impl_m;

    std::deque<message_impl> message_deque_in_m;
    std::condition_variable message_deque_in_condition;
    std::mutex message_deque_in_mutex;

    std::deque<message_impl> message_deque_out_m;
    std::mutex message_deque_out_mutex;
    std::thread message_handler_thread_m;

    message_impl message_m;


};

#endif