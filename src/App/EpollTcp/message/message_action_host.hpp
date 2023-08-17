/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_action_host.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-17 14:07:24
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __MESSAGE_ACTION_HOST__
#define __MESSAGE_ACTION_HOST__

#include "Platform_Types.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include "message_impl.hpp"
#include "spdlog/spdlog.h"
typedef std::function<void(const message_impl& message)> MessageCallback;
class ACTION
{
public:
    virtual ~ACTION()
    {
        std::cout << "Action deconstructor" << std::endl;
    }
    virtual void Do_Action(message_impl& msg) = 0;
};

#endif