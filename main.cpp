/*
 * @FilePath: /C_plus_plus_Framework/main.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-10 20:27:48
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <iostream>
#include <sys/prctl.h>
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
#include "message_handler.hpp"
#include "message_header.hpp"
#include "message_impl.hpp"
#include "routing_manager.hpp"

void spdlog_test()
{

    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");
}

void json_test()
{
    nlohmann::json j;

    // add a number that is stored as double (note the implicit conversion of j to an object)
    j["pi"] = 3.141;
    // add a Boolean that is stored as bool
    j["happy"] = true;
    // add a string that is stored as std::string
    j["name"] = "Niels";
    // add another null object by passing nullptr
    j["nothing"] = nullptr;
    // add an object inside the object
    j["answer"]["everything"] = 42;
    // add an array that is stored as std::vector (using an initializer list)
    j["list"] = { 1, 0, 2 };
    // add another object (using an initializer list of pairs)
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };

    std::cout << j << std::endl;
    std::string json_string = j.dump(4);
    std::cout << json_string << std::endl;

    nlohmann::json j_parse = nlohmann::json::parse(json_string);
    if(j_parse.contains("pi"))
    {
        float pi = j_parse["pi"];
        std::cout << pi << std::endl;
    }

}

void log_test()
{
    /*
     *write async log file
     */
    auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "/home/thor/Desktop/Reconsitution_C++/log/async_log.txt");  
    SPDLOG_LOGGER_INFO(async_file,"test");

    /*
     *write bin file
     */
    std::ofstream ofs;
    ofs.open("/home/thor/Desktop/Reconsitution_C++/log/bin_log.txt",std::ios::binary | std::ios::app);
    uint8_t buffer[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    
    ofs.write((const char *)buffer,sizeof(buffer));
    // ofs << "hello world" << 1 << "world" << 2;
}

static void callback(sint32 clientfd,void* data,uint32 len)
{
//   struct Message {
//     int number;
//     uint32_t len;
//     void* text;
// };

    // Message message;
    // memcpy(&message.number,data,4);
    // memcpy(&message.len,data+4,4);
    // message.text = new uint8[message.len];
    // memcpy(message.text,data+8,message.len);
    // char tmpstr[message.len] = {0};
    // strncpy(tmpstr,(const char*)message.text,message.len);
    // spdlog::info("recv message number [{:d}] text [{}]", message.number,message.text);
    // std::cout << "recv message number " << message.number << "message text " << tmpstr << std::endl;
    // std::cout << "epoll callback clientfd " << clientfd << " len " << len << std::endl;
    // delete[] message.text;
}

static void callback2(sint32 clientfd,void* data,uint32 len)
{
    std::cout << "epoll callback clientfd " << clientfd << " len " << len << std::endl;
}
void EpollTcp_Test()
{
    std::string path("/tmp/localsocket");
    std::string path1("/tmp/localsocket1");
    EpollServer *server = new EpollServer();
    static IPCServer ipc1(callback,path);
    static IPCServer ipc2(callback2,path1);

    // server->Epoll_AddEvent(ipc1);
    // server->Epoll_AddEvent(ipc2);
    server->Epoll_AddEvent(&ipc1);
    server->Epoll_AddEvent(&ipc2);

    // server->Epoll_AddEvent(std::move(ipc1));
    // server->Epoll_AddEvent(std::move(ipc2));
    // server->Epoll_DelEvent(&ipc1);
    // server->Epoll_DelEvent(ipc2);
}

void Observer_test()
{
    std::shared_ptr<Observer> pobserver_0 = ConcreteObserver_sample_0::get_instance();
    std::shared_ptr<Observer> pobserver_1 = ConcreteObserver_sample_1::get_instance();

    std::shared_ptr<Subject> subject = ConcreteSubject_0::get_instance();

    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_1, pobserver_0);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_2, pobserver_0);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_3, pobserver_0);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_4, pobserver_0);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_1, pobserver_1);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_2, pobserver_1);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_3, pobserver_1);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_4, pobserver_1);
    
#if 0
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_1,pobserver_0);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_2,pobserver_0);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_3,pobserver_0);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_4,pobserver_0);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_1,pobserver_1);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_2,pobserver_1);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_3,pobserver_1);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_4,pobserver_1);
#endif
    uint8_t datatest[5] = {0x00,0x01,0x02,0x03,0x04};
    subject->Notify(ConcreteSubject_0::SOA_TYPE_1, datatest, sizeof(datatest));
    subject->Notify(ConcreteSubject_0::SOA_TYPE_2, datatest, sizeof(datatest));
    subject->Notify(ConcreteSubject_0::SOA_TYPE_3, datatest, sizeof(datatest));
    subject->Notify(ConcreteSubject_0::SOA_TYPE_4, datatest, sizeof(datatest));
}



int main(int argc, char **argv)
{
    pid_t pid = getpid();
    std::cout << "当前进程的PID: " << pid << std::endl;
    pthread_setname_np(pthread_self(), "Main Thread");
    // message_handler mesghandler;
    // mesghandler.action(_COM_CMD_TYPES_::COM_CMD_LOGIN);
    // mesghandler.action(_COM_CMD_TYPES_::COM_CMD_LOGOUT);
    // mesghandler.action(_COM_CMD_TYPES_::COM_CMD_CHECK);
    // mesghandler.action(_COM_CMD_TYPES_::COM_CMD_FORWARD);
    // mesghandler.action(_COM_CMD_TYPES_::COM_CMD_BROADCAST);
    // mesghandler.action((_COM_CMD_TYPES_)6);

    // Observer_test();
    // test_findprotocolheader();
    // test_serializer();
    // test_serializer_queue();
    // test_praseprotocol();

    // test_();

    EpollTcp_Test();

    // json_test();
    // spdlog_test();
    // log_test();
    // EpollTcp_Test();
    while(1)
    {
        // std::cout << "main thread" << std::endl;
        sleep(1);
    }

    return 0;
}
