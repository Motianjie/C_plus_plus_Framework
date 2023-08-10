/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/routing/routing_manager.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-10 19:57:50
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __ROUTING_MANAGER__
#define __ROUTING_MANAGER__
#include "Platform_Types.hpp"
#include "utility.hpp"
#include "message_handler.hpp"
#include "routing_tables.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"
#include <memory>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

class message_handler;
class serializer;
class deserializer;
class routing_tables;
/**
 * @brief: 该类用以连接messagehandler类和EpollServer类
 * 接收来自EpollServer的序列化二进制数据流并在主线程中读取和处理
 * 解析到对应的消息体，按照应用逻辑传递给message_handler处理
 */
class routing_manager
{
public:
    routing_manager();
    ~routing_manager();

public:
    std::shared_ptr<serializer> get_serializer();
    void put_serializer(const std::shared_ptr<serializer> &_serializer);
    std::shared_ptr<deserializer> get_deserializer();
    void put_deserializer(const std::shared_ptr<deserializer> &_deserializer);

public:
    void routing_manager_thread(void);//routing主线程

public:
    boolean push_data(sint32 clientfd,const uint8 *data, const uint32 len);
    boolean push_data(const uint8 *data, const uint32 len);
    void ParseProtocal();
    boolean pop_send_data(sint32& clientfd,uint8** data,uint32& len);

    void push_message_out(message_impl& mesg);

    private:
    message_handler message_handler_m;
    routing_tables routing_tables_m;

    private:
    std::queue<std::shared_ptr<serializer>> serializers_;
    std::mutex serializer_mutex_;
    std::condition_variable serializer_condition_;

    std::queue<std::shared_ptr<deserializer>> deserializers_;
    std::mutex deserializer_mutex_;
    std::condition_variable deserializer_condition_;

    std::mutex data_mutex;
    std::mutex pushdata_mutex_;
    std::condition_variable pushdata_condition_;
    std::thread routing_manager_thread_m;

    private:
    std::vector<uint8> data_raw_in; //存储client发送的二进制数据流
    std::vector<uint8>::iterator position_;
    uint32 remaining_;

    private:
    message_impl message_m;
    uint8* send_buff_m;
    uint32 send_len_m;
    std::mutex send_buff_mutex_;

};





#endif