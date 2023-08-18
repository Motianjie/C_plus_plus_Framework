/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/EpollServer.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-18 17:20:23
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef _EPOLLSERVER_HPP_
#define _EPOLLSERVER_HPP_
#include <sys/epoll.h>
#include "IPCServer.hpp"
#include "routing_manager.hpp"
#include <thread>
#include <pthread.h>
#include <map>
#include <vector>
#include <list>

#include "thread_set.hpp"
#define MAX_EVENTS_M 255

/**
 * @brief Epoll master类
 * 实现对注册的ipc，rpc通信管理，通过回调函数将客户端消息转发
 * todo: implement send function
 */
class EpollServer
{
private:
    /* data */
public:
    EpollServer() : EpollServer_thread_m(std::bind(&EpollServer::Epoll_Thread,this)),
                    EpollServer_thread_send_m(std::bind(&EpollServer::Epoll_Thread_Send,this))
    {   

    };
    ~EpollServer();
    
    boolean Epoll_AddEvent(IPCServer* ipcserver_ptr);
    // boolean Epoll_AddEvent( IPCServer&& ipcserver);
    // boolean Epoll_AddEvent(const IPCServer& ipcserver);
    boolean Epoll_AddEvent(sint32 sockfd);
    boolean Epoll_DelEvent(IPCServer* ipcserver_ptr);
    // boolean Epoll_DelEvent(const IPCServer& ipcserver);
private:
    sint32 Epoll_Create(void);
    sint32 Epoll_Wait(void);
    void Epoll_Thread(void);
    void Epoll_Thread_Send(void);
    sint32 epfd_m;
    struct epoll_event evt_m[MAX_EVENTS_M];
    std::thread EpollServer_thread_m;
    std::thread EpollServer_thread_send_m;
    //std::list<IPCServer> ipc_m;//拷贝一份对象存下来，对象生命周期无需控制，但是无法跟随对象的成员变化而变化
    std::list<IPCServer*> ipc_ptr_m;//存指针，对象的生命周期要控制，不能在运行期间销毁掉，但是能直接操控对象
    static const uint32 RecvBufferSize = 16*1024u;//最大接收数据量
    static const uint32 OneTimeRecvSize = 2*1024u;//每次接收数据量
    routing_manager routing_manager_m;
};

#endif


