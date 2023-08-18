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
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"
#include "EpollServer.hpp"
#include "Platform_Types.hpp"
#include "testcase.hpp"
#include "message_handler.hpp"
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
    message_header test_header(0x23242526,0,0x0203,0x0405,0x0607,_COM_CMD_TYPES_::COM_CMD_FORWARD,0x0809);//测试消息体头部
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


// static routing_manager routing_manager_instance;
void worker()
{
    while(1)
    {
        // routing_manager_instance.get_serializer();
        // std::cout << "get serializer " << std::endl;
        // routing_manager_instance.get_deserializer();
        // std::cout << "get deserializer " << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void test_serializer_queue()
{
    std::thread t(worker);
    while(1)
    {
        // std::shared_ptr<serializer> serialinstance;
        // std::shared_ptr<deserializer> deserialinstance;
 
        // routing_manager_instance.put_serializer(serialinstance);
        // std::cout << "put serializer " << std::endl;
        // routing_manager_instance.put_deserializer(deserialinstance);
        // std::cout << "put deserializer " << std::endl;
        // sleep(10);
    }
}

std::vector<uint8_t>::iterator test_findProtocolHeader(std::vector<uint8_t>& data, std::vector<uint8_t>& header)
{
    auto headerPos = std::search(data.begin(), data.end(), header.begin(), header.end());
    return headerPos;
}

void test_findprotocolheader()
{
// 示例函数：在二进制数据流中查找协议头
    std::vector<uint8_t> data = { 0x01,0x23, 0x24, 0x25, 0x26, 0x02, 0x03 };
    std::vector<uint8_t> header = { 0x23, 0x24, 0x25, 0x26};
    auto headerPos = test_findProtocolHeader(data, header);
    if (headerPos != data.end()) {
        // uint32 distance = std::distance(data.begin(), headerPos);
        // std::cout << "Protocol header found at position: " << distance << std::endl;
        std::cout << "Protocol header found at position: " << std::distance(data.begin(), headerPos) << std::endl;
    } else {
        std::cout << "Protocol header not found!" << std::endl;
    }
}

void test_exception()
{
    routing_manager routing_manager_instance;
    message_header test_header(0x23242526,0,(uint32)_IPC_ID_::_COM_CLIENT_1_,(uint32)_IPC_ID_::_COM_SERVER_,(uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_REQ),_COM_CMD_TYPES_::COM_CMD_LOGIN,0x0809);//测试LOGIN消息体头部
    uint8 payload[] = {0x11,0x12,0x13,0x14,0x15};//测试消息体payload
    //构造消息体
    message_impl test_message((const message_header&)test_header,(const uint32)sizeof(payload),(const uint8*)&payload);
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
    uint8 tmp[] = {0x23,0x24,0x25,0x26,0x00,0x01,0x02};
    header_serializer->set_data(tmp,sizeof(tmp));
    routing_manager_instance.push_data((uint8*)header_serializer->get_data(), header_serializer->get_size());
    sleep(1);
    while(1)
    {
        sleep(1);
        routing_manager_instance.push_data((uint8*)header_serializer->get_data(), header_serializer->get_size());
    }
}


void test_praseprotocol()
{
    routing_manager routing_manager_instance;

    /*client 1 login*/
    message_header test_header_login_client1(0x23242526,0,(uint32)_IPC_ID_::_COM_CLIENT_1_,(uint32)_IPC_ID_::_COM_SERVER_,(uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_REQ),_COM_CMD_TYPES_::COM_CMD_LOGIN,0x0809);//测试LOGIN消息体头部
    uint8 payload[] = {0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,0x11,0x12,0x13,0x14,0x15};//测试消息体payload
    //构造消息体
    message_impl test_message_login_client1((const message_header&)test_header_login_client1,(const uint32)sizeof(payload),(const uint8*)&payload);

    std::cout << "send test" << std::endl;
    //从序列化器队列中获取一个序列化器
    auto serializer_login_client1 = routing_manager_instance.get_serializer();
    //序列化头部和payload
    if(test_message_login_client1.message_header_m.serialize(serializer_login_client1) && test_message_login_client1.serialize(serializer_login_client1))
    {
        std::cout << "序列化成功" << std::endl;
    }else
    {
        serializer_login_client1->reset();
        routing_manager_instance.put_serializer(serializer_login_client1);
        return;
    }
    sint32 client_id_client1 = 0x05;
    routing_manager_instance.push_data(client_id_client1,(uint8*)serializer_login_client1->get_data(), serializer_login_client1->get_size());
    routing_manager_instance.push_data((uint8*)serializer_login_client1->get_data(), serializer_login_client1->get_size());

    serializer_login_client1->reset();
    routing_manager_instance.put_serializer(serializer_login_client1);

    /*client 2 login*/
    message_header test_header_login_client2(0x23242526,0,(uint32)_IPC_ID_::_COM_CLIENT_2_,(uint32)_IPC_ID_::_COM_SERVER_,(uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_REQ),_COM_CMD_TYPES_::COM_CMD_LOGIN,0x0809);//测试LOGIN消息体头部
    //构造消息体
    message_impl test_message_login_client2((const message_header&)test_header_login_client2,(const uint32)sizeof(payload),(const uint8*)&payload);

    std::cout << "send test" << std::endl;
    //从序列化器队列中获取一个序列化器
    auto serializer_login_client2 = routing_manager_instance.get_serializer();
    //序列化头部和payload
    if(test_message_login_client2.message_header_m.serialize(serializer_login_client2) && test_message_login_client2.serialize(serializer_login_client2))
    {
        std::cout << "序列化成功" << std::endl;
    }else
    {
        serializer_login_client2->reset();
        routing_manager_instance.put_serializer(serializer_login_client2);
        return;
    }
    sint32 client_id_client2 = 0x06;
    routing_manager_instance.push_data(client_id_client2,(uint8*)serializer_login_client2->get_data(), serializer_login_client2->get_size());
    routing_manager_instance.push_data((uint8*)serializer_login_client2->get_data(), serializer_login_client2->get_size());

    serializer_login_client2->reset();
    routing_manager_instance.put_serializer(serializer_login_client2);

    /*client 3 login*/
    message_header test_header_login_client3(0x23242526,0,(uint32)_IPC_ID_::_COM_CLIENT_3_,(uint32)_IPC_ID_::_COM_SERVER_,(uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_REQ),_COM_CMD_TYPES_::COM_CMD_LOGIN,0x0809);//测试LOGIN消息体头部
    //构造消息体
    message_impl test_message_login_client3((const message_header&)test_header_login_client3,(const uint32)sizeof(payload),(const uint8*)&payload);

    std::cout << "send test" << std::endl;
    //从序列化器队列中获取一个序列化器
    auto serializer_login_client3 = routing_manager_instance.get_serializer();
    //序列化头部和payload
    if(test_message_login_client3.message_header_m.serialize(serializer_login_client3) && test_message_login_client3.serialize(serializer_login_client3))
    {
        std::cout << "序列化成功" << std::endl;
    }else
    {
        serializer_login_client3->reset();
        routing_manager_instance.put_serializer(serializer_login_client3);
        return;
    }
    sint32 client_id_client3 = 0x07;
    routing_manager_instance.push_data(client_id_client3,(uint8*)serializer_login_client3->get_data(), serializer_login_client3->get_size());
    routing_manager_instance.push_data((uint8*)serializer_login_client3->get_data(), serializer_login_client3->get_size());
    
    serializer_login_client2->reset();
    routing_manager_instance.put_serializer(serializer_login_client2);

    /*check*/
    message_header test_header_check(0x23242526,0,(uint32)_IPC_ID_::_COM_CLIENT_1_,(uint32)_IPC_ID_::_COM_SERVER_,(uint32)(_CHECK_TOPIC_TYPE_::_COM_CMD_CHECK_TOPIC_REQ),_COM_CMD_TYPES_::COM_CMD_CHECK,0x0809);//测试LOGIN消息体头部
    //构造消息体
    message_impl test_message_check((const message_header&)test_header_check,(const uint32)sizeof(payload),(const uint8*)&payload);

    std::cout << "send test" << std::endl;
    //从序列化器队列中获取一个序列化器
    auto header_serializer_ = routing_manager_instance.get_serializer();
    //序列化头部和payload
    if(test_message_check.message_header_m.serialize(header_serializer_) && test_message_check.serialize(header_serializer_))
    {
        std::cout << "序列化成功" << std::endl;
    }else
    {
        header_serializer_->reset();
        routing_manager_instance.put_serializer(header_serializer_);
        return;
    }

    header_serializer_->reset();
    routing_manager_instance.put_serializer(header_serializer_);

    /*broadcast*/
    message_header test_header_broadcast(0x23242526,0,(uint32)_IPC_ID_::_COM_CLIENT_1_,(uint32)_IPC_ID_::_COM_SERVER_,(uint32)(_LOGIN_TOPIC_TYPE_::_COM_CMD_LOGIN_TOPIC_REQ),_COM_CMD_TYPES_::COM_CMD_BROADCAST,0x0809);//测试LOGIN消息体头部
    //构造消息体
    message_impl test_message_broadcast((const message_header&)test_header_broadcast,(const uint32)sizeof(payload),(const uint8*)&payload);

    std::cout << "send test" << std::endl;
    //从序列化器队列中获取一个序列化器
    auto serializer_broadcast = routing_manager_instance.get_serializer();
    //序列化头部和payload
    if(test_message_broadcast.message_header_m.serialize(serializer_broadcast) && test_message_broadcast.serialize(serializer_broadcast))
    {
        std::cout << "序列化成功" << std::endl;
    }else
    {
        serializer_broadcast->reset();
        routing_manager_instance.put_serializer(serializer_broadcast);
        return;
    }
    routing_manager_instance.push_data((uint8*)serializer_broadcast->get_data(), serializer_broadcast->get_size());
    
    // serializer_broadcast->reset();
    // serializer_broadcast.put_serializer(serializer_broadcast);
    
    //send data 测试
    uint8* data = nullptr;
    uint32 len;
    sint32 clientfd =-1;
    // routing_manager_instance.push_message_out(test_message);
    while(1)
    {
        if(routing_manager_instance.pop_send_data(clientfd,&data,len))
        {
            std::vector<uint8> tmpvec;
            tmpvec.insert(tmpvec.end(),data,data+len);
            spdlog::info("show_message payload_len[{}] payload elements:{}",len,spdlog::to_hex(tmpvec));
            tmpvec.clear();
        }
        sleep(1);
        routing_manager_instance.push_data((uint8*)serializer_broadcast->get_data(), serializer_broadcast->get_size());
    }
    
    
    // while(1)
    // {
    //     // routing_manager_instance.push_data((uint8*)&tmp,4);//插入异常字段干扰
    //      routing_manager_instance.push_data((uint8*)header_serializer->get_data(), header_serializer->get_size());
    //     // routing_manager_instance.push_data((uint8*)&tmp,4);
    //     sleep(1);
    // }

}

