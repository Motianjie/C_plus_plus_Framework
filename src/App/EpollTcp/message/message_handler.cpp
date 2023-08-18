/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_handler.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-18 18:20:06
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "message_handler.hpp"

message_handler::message_handler(const std::shared_ptr<routing_tables>& _routing_tables) :  routing_tables_m(_routing_tables),
                                                                                            message_handler_thread_m(std::bind(&message_handler::message_handler_thread,this))                                                                                       
{

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
    static uint32 cnt = 0;
    static uint32 cnt_expect = 0u;
    static uint16 frame_cnt;
    static uint16 message_cnt = 0u;
    static auto startTime = std::chrono::high_resolution_clock::now();
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

        cnt = message.message_header_m.get_cnt();
        if(cnt_expect != cnt)
        {
            // spdlog::error("cnt mismatch cnt[{:d}] cnt_expect[{:d}]",cnt,cnt_expect);
        }else
        {
            // spdlog::info("cnt match cnt[{:d}] cnt_expect[{:d}]",cnt,cnt_expect);
        }
        cnt_expect = ++cnt;
        if(cnt_expect > 255)
        {
            cnt_expect = 0u;
        }
        frame_cnt++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        if(duration >= 60000)
        {
            spdlog::error("frame_cnt_recv[{:d}]",frame_cnt);
            frame_cnt=0u;
            startTime = currentTime;
        }
        if(!message_action_impl_m)
            message_action_impl_m = std::make_shared<message_action_impl>(routing_tables_m,shared_from_this());

        message_action_impl_m->action(message.message_header_m.get_cmd_id(),message);
        
        message_deque_in_m.pop_front();
        #ifdef DEBUG
        spdlog::info("message action cnt[{}]",message_cnt);
        #endif
    }
}

void message_handler::message_handler_thread()
{
    thread_set thread_set_("message_handler_thread",message_handler_thread_m,1);
    std::cout << "message_handler_thread created" << std::endl;
    message_handler_thread_m.detach();
    while(1)
    {
        message_handle();
        // std::cout << "message_handler_thread" << std::endl;
    }
}
