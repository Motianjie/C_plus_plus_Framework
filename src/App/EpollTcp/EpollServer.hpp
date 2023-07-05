#ifndef _EPOLLSERVER_HPP_
#define _EPOLLSERVER_HPP_
#include <sys/epoll.h>
#include "IPCServer.hpp"
#include <thread>
#include <pthread.h>
#include <map>
#include <vector>
#define MAX_EVENTS_M 255


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
    boolean Epoll_AddEvent(sint32 sockfd);
    boolean Epoll_DelEvent( IPCServer& ipcserver);
private:
    sint32 Epoll_Create(void);

    sint32 Epoll_Wait(void);

    void Epoll_Thread(void);

    sint32 epfd_m;
    struct epoll_event evt_m[MAX_EVENTS_M];
    std::thread EpollServer_thread_m;
    std::vector<IPCServer> ipc_m;
};

#endif


