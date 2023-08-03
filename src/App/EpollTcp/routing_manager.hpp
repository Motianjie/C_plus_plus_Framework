/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/routing_manager.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-03 10:22:58
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __ROUTING_MANAGER__
#define __ROUTING_MANAGER__
#include "Platform_Types.hpp"
#include "serializer.hpp"
#include "deserializer.hpp"
#include <memory>
#include <queue>
#include <condition_variable>
#include <mutex>

class routing_manager
{
public:
    routing_manager(/* args */);
    ~routing_manager();

    std::shared_ptr<serializer> get_serializer();
    void put_serializer(const std::shared_ptr<serializer> &_serializer);
    std::shared_ptr<deserializer> get_deserializer();
    void put_deserializer(const std::shared_ptr<deserializer> &_deserializer);


    private:
    std::queue<std::shared_ptr<serializer>> serializers_;
    std::mutex serializer_mutex_;
    std::condition_variable serializer_condition_;

    std::queue<std::shared_ptr<deserializer>> deserializers_;
    std::mutex deserializer_mutex_;
    std::condition_variable deserializer_condition_;
};





#endif