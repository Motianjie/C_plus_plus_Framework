#ifndef _EPOLLSERVER_HPP_
#define _EPOLLSERVER_HPP_
#include <sys/epoll.h>
#include "IPCServer.hpp"
#include <thread>
#include <pthread.h>
#include <unordered_map>
#define MAX_EVENTS_M 255


class EpollServer : public IPCServer
{
private:
    /* data */
public:
    EpollServer(RecvCallback callback_in,std::string ipcfile) : IPCServer(callback_in,ipcfile),
                                                                EpollServer_thread_m(std::bind(&EpollServer::Epoll_Thread,this))
    {
    };
    ~EpollServer() override;


private:
    sint32 Epoll_Create(void);
    boolean Epoll_AddEvent(sint32 sockfd);
    boolean Epoll_DelEvent(sint32 sockfd);
    sint32 Epoll_Wait(void);

    void Epoll_Thread(void);
    sint32 epfd_m;
    struct epoll_event evt_m[MAX_EVENTS_M];
    std::thread EpollServer_thread_m;
    std::unordered_map<sint32,RecvCallback> epoll_events_map_m;
    static void epoll_recv_callback_m(sint32 clientfd,void* data,uint32 len);
};

#endif


