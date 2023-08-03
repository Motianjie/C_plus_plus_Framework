/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message_handler.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-03 15:40:30
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "message_handler.hpp"


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