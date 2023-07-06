#ifndef _EPOLLSERVER_HPP_
#define _EPOLLSERVER_HPP_
#include <sys/epoll.h>
#include "IPCServer.hpp"
#include <thread>
#include <pthread.h>
#include <map>
#include <vector>
#include <list>
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
    EpollServer() : EpollServer_thread_m(std::bind(&EpollServer::Epoll_Thread,this))
    {   
    };
    ~EpollServer();
    boolean Epoll_AddEvent( IPCServer&& ipcserver);
    boolean Epoll_AddEvent(const IPCServer& ipcserver);
    boolean Epoll_AddEvent(sint32 sockfd);
    boolean Epoll_DelEvent(const IPCServer& ipcserver);
private:
    sint32 Epoll_Create(void);
    sint32 Epoll_Wait(void);
    void Epoll_Thread(void);
    sint32 epfd_m;
    struct epoll_event evt_m[MAX_EVENTS_M];
    std::thread EpollServer_thread_m;
    std::list<IPCServer> ipc_m;
    const uint32 RecvBufferSize = 16*1024u;//最大接收数据量
    const uint32 OneTimeRecvSize = 2*1024u;//每次接收数据量
};

#endif


