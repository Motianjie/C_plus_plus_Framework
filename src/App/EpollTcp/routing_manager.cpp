/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/routing_manager.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-04 17:19:18
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "routing_manager.hpp"

routing_manager::routing_manager() : routing_manager_thread_m(std::bind(&routing_manager::routing_manager_thread,this)),
                                     position_(data_raw_in.begin()),
                                     remaining_(0)
{
    uint32 it_max = 5;
    for(int i = 0;i < it_max;++i)
    {
        serializers_.push(std::make_shared<serializer>());
        deserializers_.push(std::make_shared<deserializer>());
    }
}

routing_manager::~routing_manager()
{
    routing_manager_thread_m.join();
}

std::shared_ptr<serializer> routing_manager::get_serializer()
{
    std::unique_lock<std::mutex> its_lock(serializer_mutex_);
    while (serializers_.empty())
    {
        std::cout << " has no available serializer. Waiting..." << std::endl;
        serializer_condition_.wait(its_lock);
        std::cout << " now checking for available serializer." << std::endl;
    } 

    auto it_serializer = serializers_.front();
    serializers_.pop();
    return it_serializer;
}

void routing_manager::put_serializer(const std::shared_ptr<serializer> &_serializer)
{
    std::unique_lock<std::mutex> its_lock(serializer_mutex_);
    serializers_.push(_serializer);
    serializer_condition_.notify_one();
}

std::shared_ptr<deserializer> routing_manager::get_deserializer()
{
    std::unique_lock<std::mutex> its_lock(deserializer_mutex_);
    while (deserializers_.empty())
    {
        std::cout << " has no available deserializer. Waiting..." << std::endl;
        deserializer_condition_.wait(its_lock);
        std::cout << " now checking for deavailable serializer." << std::endl;
    } 

    auto it_deserializer = deserializers_.front();
    deserializers_.pop();
    return it_deserializer;
}

void routing_manager::put_deserializer(const std::shared_ptr<deserializer> &_deserializer)
{
    std::unique_lock<std::mutex> its_lock(deserializer_mutex_);
    deserializers_.push(_deserializer);
    deserializer_condition_.notify_one();
}

boolean routing_manager::push_data(const uint8 *data, const uint32 len)
{
    if(data == nullptr || len == 0)
        return false;

    try
    {
        std::unique_lock<std::mutex> it_lock(pushdata_mutex_);
        data_raw_in.insert(data_raw_in.end(),data,data+len);
        pushdata_condition_.notify_one();
    }catch(const std::bad_alloc& e)
    {
        std::cout << "bad alloc" << e.what() << std::endl;
        return false;
    }
    return true;
}

void routing_manager::ParseProtocal(void)
{    
    std::unique_lock<std::mutex> it_lock(pushdata_mutex_);
    while(data_raw_in.empty())
    {
        pushdata_condition_.wait(it_lock);
    }
    std::vector<uint8_t> header = { 0x23, 0x24, 0x25, 0x26};
    auto headerPos = findProtocolHeader(data_raw_in, header);
    uint32 distance;
    if(headerPos != data_raw_in.end())
    {
        distance = std::distance(data_raw_in.begin(), headerPos);
        //std::cout << "Protocol header found at position: " << distance << std::endl;
    }else
    {
        std::cout << "Protocol header not found!" << std::endl;
        return;
    }

    auto deserializer_ = this->get_deserializer();
    headerPos = deserializer_->data_.begin();
    deserializer_->append_data(data_raw_in.data() + distance,data_raw_in.size() - distance);
    
    while( (headerPos = findProtocolHeader(deserializer_->data_, header)) != deserializer_->data_.end() )
    {
        //找到协议头
        static uint16 mesg_cnt = 0u;
        static uint16 mesg_err_cnt = 0u;
        mesg_cnt++;
        message_impl message_;
        if( message_.message_header_m.deserialize(deserializer_) && message_.deserialize(deserializer_) )
        {
            message_.message_header_m.show_header();
            message_.show_message();
            spdlog::info("message cnt:[{:d}]",mesg_cnt); 
            message_handler_m.put_message(message_);
        }else
        {
            mesg_err_cnt++;
            spdlog::error("deserialize error mesg_err_cnt[{:d}]",mesg_err_cnt);
        }
        distance = std::distance(deserializer_->data_.begin(),deserializer_->position_);
        deserializer_->set_data(deserializer_->data_.data() + distance,deserializer_->data_.size() - distance);
    }

    data_raw_in.clear();
    deserializer_->reset();
    this->put_deserializer(deserializer_);
}


void routing_manager::routing_manager_thread()
{
    std::cout << "routing_manager_thread created" << std::endl;
    std::string threadName = "routing_manager_thread";
    pthread_setname_np(pthread_self(), threadName.c_str());
    // routing_manager_thread_m.detach();
    while(1)
    {
        ParseProtocal();
        std::cout << "routing_manager_thread is running" << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}