#include "EpollServer.hpp"

EpollServer::~EpollServer()
{
    close(epfd_m);
    std::cout << "EpollServer destructor" << std::endl;
}

sint32 EpollServer::Epoll_Create(void)
{
    int epoll_fd = epoll_create1(0U);
    return epoll_fd;
}

boolean EpollServer::Epoll_AddEvent(sint32 sockfd)
{
    struct epoll_event  ev;
    ev.events   = EPOLLIN;
    ev.data.fd  = sockfd;

    // epoll_events_map_m[ev.data.fd] = recv_callback;//insert event and callback

    while(epoll_ctl(epfd_m, EPOLL_CTL_ADD, sockfd, &ev) == -1)
    {
        printf("unix socket fd=%d server add epoll list error: %s",sockfd, strerror(errno));
        return false;
    }
    return true;
}

 boolean EpollServer::Epoll_DelEvent(sint32 sockfd)
 {
    struct epoll_event  ev;
    ev.events   = EPOLLIN;
    ev.data.fd  = sockfd;

    epoll_events_map_m.erase(ev.data.fd);//erase event and callback

    while(epoll_ctl(epfd_m, EPOLL_CTL_DEL, sockfd, &ev) == -1)
    {
        printf("unix socket fd=%d server del epoll list error: %s",sockfd, strerror(errno));
        return false;
    }
    return true;
}

void EpollServer::epoll_recv_callback_m(sint32 clientfd, void *data, uint32 len)
{
    std::cout << "EpollServer recv message " << clientfd << " " << len << std::endl;
}

sint32 EpollServer::Epoll_Wait(void)
{
    return epoll_wait(epfd_m,evt_m, MAX_EVENTS_M, -1);
}

 void EpollServer::Epoll_Thread(void)
 {
    std::cout << "Epoll thread created" << std::endl;
    std::string threadName = "Epoll_Thread";
    EpollServer_thread_m.detach();//
    pthread_setname_np(pthread_self(), threadName.c_str());
    
    sint32 clt_sock;
    uint32 recvlen;
    uint8 buff[8000];
    char buff1[8000];

    epfd_m = Epoll_Create();
    Epoll_AddEvent(un_sock_m);

    while (1)
    {
        sint32 act_epoll_fds = Epoll_Wait();
        for(sint32 i = 0; i < act_epoll_fds; ++i)
        {
            int32_t fd_idx = evt_m[i].data.fd;
            if(fd_idx == un_sock_m)//new client socket
            {
                clt_sock = Accept(un_sock_m);
                if(clt_sock != -1)
                {
                    std::cout << "ipc socket accepted:" << clt_sock << std::endl;
                    Set_Nonblocking(clt_sock);
                    Set_PortReuse(clt_sock);
                    Epoll_AddEvent(clt_sock);
                }
                
            }else if(evt_m[i].events&EPOLLIN)
            {
                recvlen = recv(fd_idx, (char *)buff, (size_t)((ssize_t)1024), 0);
                if(recvlen == -1)
                {
                    std::cout << "fail to read socket" << std::endl;
                    close(fd_idx);
                }
                if(recvlen == 0u)
                {
                    std::cout<< "client disconnected" << std::endl;
                    close(fd_idx);
                }
                epoll_recv_callback_m(evt_m[i].data.fd,buff,recvlen);
                snprintf(buff1,recvlen,"%s\r\n",buff);
                std::cout << "recv from socket:[" << evt_m[i].data.fd << "] " << buff1 << "len is " << recvlen << std::endl;
            }else
            {
                
            }
        }
    }
    close(un_sock_m);
    close(epfd_m);
 
 }