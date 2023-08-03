#include <iostream>
#include <memory>
#include <fstream>
#include <map>
#include "Concrete_subject.hpp"
#include "Concreteobserverd_sample_0.hpp"
#include "Concreteobserverd_sample_1.hpp"
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "EpollServer.hpp"
#include "Platform_Types.hpp"
#include "testcase.hpp"
#include "MesgHandler.hpp"
#include "message_header.hpp"
#include "message_impl.hpp"
#include "routing_manager.hpp"
struct sockettest
{
    sint32 id;
    uint8 test;
    uint16 test_len;
    bool operator<(const sockettest& other) const 
    {
        return id < other.id;
    }
};

static void test_cb(sint32 did,void* data,uint32 len)
{
    std::cout << "test_cb"<<std::endl;
}

static std::function<void(sint32,void*,uint32)> func = std::bind(&test_cb,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);

void test_()//测试std::map的键可以是自定义的结构体，但是要重写<,值也可以是函数指针
{
    sint32 did =2;
    uint8 buffer[10] = {1};
    uint32 len =sizeof(buffer);
    // std::map<struct sockettest,void(*)(sint32,void*,uint32)> maptest;
    std::map<struct sockettest,std::function<void(sint32,void*,uint32)>> maptest;
    sockettest test1;
    test1.test = 1;
    test1.test_len = 10;

    sockettest test2;
    test2.test = 2;
    test2.test_len = 20;

    maptest.insert(std::make_pair(test1,func));
    maptest.insert(std::make_pair(test2,func));

    for(auto maps : maptest)
    {
        maps.second(did,buffer,len);
    }
}

void test_serializer()
{
    routing_manager routing_manager_instance;
    message_impl test_message;

    test_message.message_header_m.header = 0x01;
    test_message.message_header_m.src_id = 0x0203;              /*Source identity*/
    test_message.message_header_m.dst_id = 0x0405;              /*Destination id*/
    test_message.message_header_m.topic_id = 0x0607;            /*topic identity*/
    test_message.message_header_m.cmd_id = _COM_CMD_TYPES_::COM_CMD_FORWARD;     /*com identity*/
    test_message.message_header_m.len = 0x0809;                 /*remain len without header*/
    auto header_serializer = routing_manager_instance.get_serializer();
    // serializer header_serializer;
    test_message.message_header_m.serialize(header_serializer);
    test_message.data_m.push_back(0xAA);
    test_message.data_m.push_back(0xBB);
    test_message.data_m.push_back(0xCC);
    test_message.serialize(header_serializer);

    auto header_deserializer = routing_manager_instance.get_deserializer();
    header_deserializer->set_data((uint8*)header_serializer->get_data(), header_serializer->get_size());

    message_impl test_message_de;
    test_message_de.deserialize(header_deserializer);

    header_serializer->reset();
    header_deserializer->reset();
    routing_manager_instance.put_serializer(header_serializer);
    routing_manager_instance.put_deserializer(header_deserializer);
    std::cout << "test_serializer finsished " << std::endl;
}


static routing_manager routing_manager_instance;
void worker()
{
    while(1)
    {
        routing_manager_instance.get_serializer();
        std::cout << "get serializer " << std::endl;
        routing_manager_instance.get_deserializer();
        std::cout << "get deserializer " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void test_serializer_queue()
{
    std::thread t(worker);
    while(1)
    {
        std::shared_ptr<serializer> serialinstance;
        std::shared_ptr<deserializer> deserialinstance;
 
        routing_manager_instance.put_serializer(serialinstance);
        std::cout << "put serializer " << std::endl;
        routing_manager_instance.put_deserializer(deserialinstance);
        std::cout << "put deserializer " << std::endl;
        sleep(10);
    }
}