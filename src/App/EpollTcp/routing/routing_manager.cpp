/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/routing/routing_manager.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-11 17:15:27
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "routing_manager.hpp"

routing_manager::routing_manager() : routing_manager_thread_m(std::bind(&routing_manager::routing_manager_thread,this)),
                                     position_(data_raw_in.begin()),
                                     remaining_(0),
                                     send_len_m(8096)
{
    uint32 it_max = 5;
    for(int i = 0;i < it_max;++i)
    {
        serializers_.push(std::make_shared<serializer>());
        deserializers_.push(std::make_shared<deserializer>());
    }
    send_buff_m = std::make_unique<uint8[]>(send_len_m);
    // send_buff_m = new uint8[send_len_m];
    
}

routing_manager::~routing_manager()
{
    // delete[] send_buff_m;
    // routing_manager_thread_m.join();
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

/**
 * @description: 需要在此处立即解析头部信息，如果是LOGIN类型，需要注册src id和client id配对的操作
 * @param {sint32} clientfd
 * @param {uint8} *data
 * @param {uint32} len
 * @return {*}
 */
boolean routing_manager::push_data(sint32 clientfd,const uint8 *data, const uint32 len)
{
    std::vector<uint8> tmpdata;
    try
    {
        tmpdata.insert(tmpdata.end(),data,data+len);
    }catch(const std::bad_alloc& e)
    {
        std::cout << "bad alloc" << e.what() << std::endl;
        return false;
    }
    std::vector<uint8_t> header = { 0x23, 0x24, 0x25, 0x26};
    auto headerPos = findProtocolHeader(tmpdata, header);
    uint32 distance;
    if(headerPos != tmpdata.end())
    {
        distance = std::distance(tmpdata.begin(), headerPos);
        //std::cout << "Protocol header found at position: " << distance << std::endl;
    }else
    {
        std::cout << "Protocol header not found!" << std::endl;
        return false;
    }
    auto deserializer_ = this->get_deserializer();
    headerPos = deserializer_->data_.begin();
    deserializer_->append_data(tmpdata.data() + distance,tmpdata.size() - distance);

    while( (headerPos = findProtocolHeader(deserializer_->data_, header)) != deserializer_->data_.end() )
    {
        //找到协议头
        static uint16 mesg_cnt = 0u;
        static uint16 mesg_err_cnt = 0u;
        mesg_cnt++;
        message_impl message_;
        if( message_.message_header_m.deserialize(deserializer_))
        {
            message_.message_header_m.show_header();
            #ifdef DEBUG
            spdlog::info("message cnt:[{:d}]",mesg_cnt); 
            #endif
            if(message_.message_header_m.get_cmd_id() == _COM_CMD_TYPES_::COM_CMD_LOGIN)
            {
                if(message_.message_header_m.get_topic_id() == (uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_REQ))
                    this->routing_tables_m.Register(clientfd,message_.message_header_m.get_src_id());
            }
            //此处进行匹配
        }else
        {
            mesg_err_cnt++;
            spdlog::error("deserialize error mesg_err_cnt[{:d}]",mesg_err_cnt);
        }
        distance = std::distance(deserializer_->data_.begin(),deserializer_->position_);
        deserializer_->set_data(deserializer_->data_.data() + distance,deserializer_->data_.size() - distance);
    }

    // data_raw_in.clear();
    deserializer_->reset();
    this->put_deserializer(deserializer_);
    return true;
}

boolean routing_manager::pop_send_data(sint32& clientfd,uint8** data,uint32& len)
{
    std::lock_guard<std::mutex> it_lock(send_buff_mutex_);  
    if(message_handler_m.pop_message(message_m))
    {
        auto serializer = this->get_serializer();
        //序列化头部和payload
        if(message_m.message_header_m.serialize(serializer) && message_m.serialize(serializer))
        {
            std::cout << "序列化成功" << std::endl;
        }else
        {
            serializer->reset();
            this->put_serializer(serializer);
            return false;
        }
        
        //根据dst id去routing_tables匹配对于的客户端的client id，并赋值给入参clientfd
        if(!routing_tables_m.routing_map(message_m.message_header_m.get_dst_id(),clientfd))
        {
            spdlog::warn("send fail:dst_id[0x{:02x}] not login",message_m.message_header_m.get_dst_id());
            serializer->reset();
            this->put_serializer(serializer);
            return false;
        }

        if((serializer->get_size() < send_len_m) && (send_buff_m!=nullptr))
        {
            std::memcpy(send_buff_m.get(),serializer->get_data(),serializer->get_size());
            #ifdef DEBUG
            std::vector<uint8> tmpvec;
            tmpvec.insert(tmpvec.end(),send_buff_m.get(),send_buff_m.get()+serializer->get_size());
            spdlog::info("sendmesaage payload_len[{}] payload elements:{}",len,spdlog::to_hex(tmpvec));
            tmpvec.clear();
            #endif
            *data = send_buff_m.get();
            len = serializer->get_size();
            serializer->reset();
            this->put_serializer(serializer);
        }else
        {
            serializer->reset();
            this->put_serializer(serializer);
            return false;
        }
    }else
    {
        return false;
    }

    return true;
}

void routing_manager::push_message_out(message_impl& mesg)
{
    message_handler_m.put_message_out(mesg);
}

void routing_manager::remove_routing(sint32 clientfd)
{
    routing_tables_m.Unregister(clientfd);
}

void routing_manager::remove_routing(uint32 src_id)
{
    routing_tables_m.Unregister(src_id);
}

void routing_manager::ParseProtocal(void)
{    
    std::unique_lock<std::mutex> it_lock(pushdata_mutex_);
    while(data_raw_in.empty())
    {
        pushdata_condition_.wait(it_lock);
    }

    if(data_raw_in.size() > 1024*10u)
    {
        spdlog::error("data_raw_in over size");
        data_raw_in.clear();
        return;
    }

    std::vector<uint8_t> header = { 0x23, 0x24, 0x25, 0x26};
    auto headerPos = findProtocolHeader(data_raw_in, header);
    uint32 distance;
    if(headerPos != data_raw_in.end())
    {
        distance = std::distance(data_raw_in.begin(), headerPos);
    }else
    {
        // std::cout << "Protocol header not found!" << std::endl;
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
            #ifdef DEBUG
            spdlog::info("message cnt:[{:d}]",mesg_cnt); 
            #endif
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
    routing_manager_thread_m.detach();
    while(1)
    {
        ParseProtocal();
    }
}