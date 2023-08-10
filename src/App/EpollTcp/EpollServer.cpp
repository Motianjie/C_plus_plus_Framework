#include "EpollServer.hpp"

EpollServer::~EpollServer()
{
    EpollServer_thread_m.join();
    close(epfd_m);
    std::cout << "EpollServer destructor" << std::endl;
}

sint32 EpollServer::Epoll_Create(void)
{
    int epoll_fd = epoll_create1(0U);
    return epoll_fd;
}

boolean EpollServer::Epoll_AddEvent(IPCServer* ipcserver_ptr)
{
    if(ipcserver_ptr)
    {
        struct epoll_event  ev;
        ev.events   = EPOLLIN;
        ev.data.fd  = ipcserver_ptr->un_sock_m;

        ipc_ptr_m.push_back(ipcserver_ptr);
        std::cout << "Add ipcserver to epoll master sockfd is " << ev.data.fd << std::endl;

        while(epoll_ctl(epfd_m, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
        {
            std::cout << " unix socket fd " << ev.data.fd << " server add epoll list error: " << strerror(errno) << std::endl;
            return false;
        }
        return true;

    }else{
        return false;
    }




}

/*============================================================================*/
/*  @brief      Add ipcserver to epoll master
 *              Asynchronous and Non Reentrant
 *  @param
 *      IPCServer
 *  @return
 *      @retval     add epoll fd result
*/
/*============================================================================*/ 
// boolean EpollServer::Epoll_AddEvent(IPCServer&& ipcserver)
// {
//     struct epoll_event  ev;
//     ev.events   = EPOLLIN;
//     ev.data.fd  = ipcserver.un_sock_m;

//     ipc_m.push_back(std::move(ipcserver));
//     std::cout << "Add ipcserver to epoll master sockfd is " << ev.data.fd << std::endl;

//     while(epoll_ctl(epfd_m, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
//     {
//         std::cout << " unix socket fd " << ev.data.fd << " server add epoll list error: " << strerror(errno) << std::endl;
//         return false;
//     }
//     return true;
// }

/*============================================================================*/
/*  @brief      Add ipcserver to epoll master 
 *              Asynchronous and Non Reentrant
 *  @param
 *      IPCServer
 *  @return
 *      @retval     add epoll fd result
*/
/*============================================================================*/ 
// boolean EpollServer::Epoll_AddEvent(const IPCServer& ipcserver)
// {
//     struct epoll_event  ev;
//     ev.events   = EPOLLIN;
//     ev.data.fd  = ipcserver.un_sock_m;

//     ipc_m.push_back(ipcserver);

//     std::cout << "Add ipcserver to epoll master sockfd is " << ev.data.fd << std::endl;
//     // epoll_events_map_m[ev.data.fd] = recv_callback;//insert event and callback

//     while(epoll_ctl(epfd_m, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
//     {
//         std::cout << " unix socket fd " << ev.data.fd << " server add epoll list error: " << strerror(errno) << std::endl;
//         return false;
//     }
//     return true;
// }
/*============================================================================*/
/*  @brief      Add clientfd to server's clients vector
 *              Asynchronous and Non Reentrant
 *  @param
 *      sint32 sockfd
 *  @return
 *      @retval     add epoll fd result
*/
/*============================================================================*/ 
boolean EpollServer::Epoll_AddEvent(sint32 sockfd)
{
    struct epoll_event  ev;
    ev.events   = EPOLLIN;
    ev.data.fd  = sockfd;

    while(epoll_ctl(epfd_m, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
    {
        std::cout << " unix socket fd " << ev.data.fd << " server add epoll list error: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

/*============================================================================*/
/*  @brief      Delete ipc server instance from epoll master
 *              Asynchronous and Non Reentrant
 *  @param
 *      const IPCServer&
 *  @return
 *      @retval     true:delete instance successful
 *                  false:delete instance failed
*/
/*============================================================================*/ 
//  boolean EpollServer::Epoll_DelEvent(const IPCServer& ipcserver)
//  {
//     struct epoll_event  ev;
//     ev.events   = EPOLLIN;
//     ev.data.fd  = ipcserver.un_sock_m;

//     for(auto it = ipc_m.begin(); it != ipc_m.end();++it)
//     {
//         if((*it).un_sock_m == ipcserver.un_sock_m)//find ipc socketfd
//         {
//             std::cout << "delete epoll event for ipcserver: " << (*it).un_sock_m << std::endl;
//             it = ipc_m.erase(it);     
//         } 
//     }
    
//     while(epoll_ctl(epfd_m, EPOLL_CTL_DEL, ev.data.fd, &ev) == -1)
//     {
//         printf("unix socket fd=%d server del epoll list error: %s",ev.data.fd, strerror(errno));
//         return false;
//     }
//     return true;
// }

boolean EpollServer::Epoll_DelEvent(IPCServer* ipcserver_ptr)
{
    struct epoll_event  ev;
    ev.events   = EPOLLIN;
    ev.data.fd  = ipcserver_ptr->un_sock_m;

    for(auto it = ipc_ptr_m.begin(); it != ipc_ptr_m.end();++it)
    {
        if((*it)->un_sock_m == ipcserver_ptr->un_sock_m)//find ipc socketfd
        {
            std::cout << "delete epoll event for ipcserver: " << (*it)->un_sock_m << std::endl;
            it = ipc_ptr_m.erase(it);     
        } 
    }
    
    while(epoll_ctl(epfd_m, EPOLL_CTL_DEL, ev.data.fd, &ev) == -1)
    {
        printf("unix socket fd=%d server del epoll list error: %s",ev.data.fd, strerror(errno));
        return false;
    }
    return true;
}
/*============================================================================*/
/*  @brief      Genernal function of epoll to wait for events
 *              Asynchronous and Non Reentrant
 *  @param
 *      
 *  @return
 *      @retval     standby epoll fds nums
 *                  
*/
/*============================================================================*/ 
sint32 EpollServer::Epoll_Wait(void)
{
    return epoll_wait(epfd_m,evt_m, MAX_EVENTS_M, -1);
}

/*============================================================================*/
/*  @brief      Main thread to handle epoll events
 *              Asynchronous and Non Reentrant
 *  @param
 *  @return               
*/
/*============================================================================*/ 
 void EpollServer::Epoll_Thread(void)
 {
    std::cout << "Epoll thread created" << std::endl;
    std::string threadName = "Epoll_Thread";
    // EpollServer_thread_m.detach();//
    pthread_setname_np(pthread_self(), threadName.c_str());
    
    sint32 clt_sock;
    uint8 buff[RecvBufferSize];

    epfd_m = Epoll_Create();
    while (1)
    {
        sint32 act_epoll_fds = Epoll_Wait();
        for(sint32 i = 0; i < act_epoll_fds; ++i)
        {
            int32_t fd_idx = evt_m[i].data.fd;
            boolean isaccept = false;
            for (auto it = ipc_ptr_m.begin(); it != ipc_ptr_m.end(); ++it)  //根据events事件的fd匹配对应的ipcserver instance
            {
                if((*it)->un_sock_m == fd_idx)
                {
                    clt_sock = (*it)->Accept((*it)->un_sock_m);//对应ipc server接受客户端连接
                    if(clt_sock != -1)
                    {
                        std::cout << "ipc server " <<  (*it)->un_sock_m << " accepted: client sock " << clt_sock << std::endl;
                        (*it)->AddIpcClient(clt_sock);   //对应ipc server加入该client到其容器
                        (*it)->Set_Nonblocking(clt_sock);
                        (*it)->Set_PortReuse(clt_sock);
                        Epoll_AddEvent(clt_sock);   //将该client fd加入epoll master
                        isaccept = true;            //标记此次循环是否发生建立连接
                    }
                }
            }
            //isaccept的作用:当客户端连接第二个服务器时，避免将建立socket类型，当作数据接收类型进行处理
            if(evt_m[i].events&EPOLLIN && isaccept == false)//满足条件即有数据可读取
            {
                uint32 index = 0u;
                sint32 tmprecvlen = 0u;
                sint32 recvlen = 0u;
                memset(buff,0u,sizeof(buff));
                //此处循环接收socket数据，每次接收OneTimeRecvSize大小，RecvBufferSize为最大接收数量
                do
                {
                    tmprecvlen = recv(fd_idx, (char *)&buff[index], (size_t)OneTimeRecvSize, 0);
                    if(tmprecvlen >0 && (recvlen+OneTimeRecvSize) < RecvBufferSize)
                    {
                        recvlen+=tmprecvlen;
                        index+=tmprecvlen;
                    }  
                }while(tmprecvlen > 0);

                if(tmprecvlen == -1)
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) 
                    {
                        // 资源暂时不可用，稍后再试，非阻塞socket在无数据到来时recv返回-1
                    }else
                    {//socket出现错误，回收对应资源
                        std::cout << "fail to read socket " << strerror(errno) <<std::endl;
                        //Del ipc server client vector
                        for (auto it = ipc_ptr_m.begin(); it != ipc_ptr_m.end(); ++it) 
                        {
                            for(auto ipc_client :(*it)->ipc_clients_m)
                            {
                                if(ipc_client.src_local_sockfd == fd_idx)
                                {
                                    (*it)->DelIpcClient(ipc_client.src_local_sockfd);
                                }
                            }
                        }   
                        close(fd_idx);
                    }
                }
                if(tmprecvlen == 0u)//客户端关闭连接
                {
                    std::cout<< "client disconnected " << strerror(errno) << std::endl;
                    //Del ipc server client vector
                    for (auto it = ipc_ptr_m.begin(); it != ipc_ptr_m.end(); ++it) 
                    {
                        for(auto ipc_client :(*it)->ipc_clients_m)
                        {
                            if(ipc_client.src_local_sockfd == fd_idx)
                            {
                                (*it)->DelIpcClient(ipc_client.src_local_sockfd);//删除对应Ipc中的Client对象
                            }
                        }
                    }   
                    close(fd_idx);//服务端回收对应socket资源
                }

                //testcase:send to client 
                #if 0
                const char* message = "Hello, client!";
                ssize_t bytesSent = send(fd_idx, message, strlen(message), 0);
                #endif
                uint8* data = nullptr;
                uint32 len = 0;
                sint32 clientfd = -1;
                while(routing_manager_m.pop_send_data(clientfd,&data,len))
                {
                    if(clientfd != -1 && data!= nullptr && len > 0)
                    {
                        ssize_t bytesSent = send(clientfd, data, len, 0);
                        if(bytesSent == -1)
                        {
                            if(errno == EAGAIN || errno == EWOULDBLOCK)
                            {
                                //发送缓冲区已满，稍后再尝试发送
                            }else
                            {
                                spdlog::error("send failed");
                            }
                        }
                    }
                        
                }

                //传递给routing_manager
                routing_manager_m.push_data(buff,(uint32)recvlen);
                //由于接收到客户端的消息，根据客户端的fd，找到对应的ipc server,并调用回调函数通知
                for (auto it = ipc_ptr_m.begin(); it != ipc_ptr_m.end(); ++it) //遍历ipcserver
                {
                    for(auto ipc_client :(*it)->ipc_clients_m)
                    {
                        if(ipc_client.src_local_sockfd == fd_idx)//找到该client所在的ipcserver
                        {
                            std::cout << "recv from clientfd "  << ipc_client.src_local_sockfd << " to ipcserver " << (*it)->un_sock_m  << std::endl;
                            if((*it)->StdRecvCallback)//防止ipc server callback nullptr情况
                                (*it)->StdRecvCallback(fd_idx,buff,recvlen);//调用该ipcserver的接收回调函数
                            else
                                std::cout << "ipcserver " << (*it)->un_sock_m <<  " callback ptr null" << std::endl;
                        }
                    }
                }  
            }
        }
    }
    close(epfd_m);//如果突发情况，回收epoll master资源
 
 }