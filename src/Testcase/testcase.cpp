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
    boolean Issuccess = false;
    routing_manager routing_manager_instance;
    message_header test_header(0x01,0x0203,0x0405,0x0607,_COM_CMD_TYPES_::COM_CMD_FORWARD,0x0809);//测试消息体头部
    uint8 payload[3] = {0xaa,0xbb,0xcc};//测试消息体payload
    //构造消息体
    message_impl test_message((const message_header&)test_header,(const uint32)sizeof(payload),(const uint8*)&payload);
    //从序列化器队列中获取一个序列化器
    auto header_serializer = routing_manager_instance.get_serializer();
    //序列化头部和payload
    if(test_message.message_header_m.serialize(header_serializer) && test_message.serialize(header_serializer))
    {
        std::cout << "序列化成功" << std::endl;
    }else
    {
        header_serializer->reset();
        routing_manager_instance.put_serializer(header_serializer);
        return;
    }
    //从反序列化器队列中获取一个反序列化器
    auto header_deserializer = routing_manager_instance.get_deserializer();
    //将序列化后的二进制数据流放入反序列化器中
    header_deserializer->set_data((uint8*)header_serializer->get_data(), header_serializer->get_size());
    //构造空消息体用以装载反序列化数据
    message_impl test_message_de;
    //反序列化头部和payload
    if(test_message_de.message_header_m.deserialize(header_deserializer) && test_message_de.deserialize(header_deserializer))
    {
        std::cout << "反序列化成功" << std::endl;
    }else
    {
        header_deserializer->reset();
        routing_manager_instance.put_deserializer(header_deserializer);
        return;
    }
    //完成后清空序列化器和反序列化器
    header_serializer->reset();
    header_deserializer->reset();
    //将用完的序列化器和反序列化器放回队列中
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