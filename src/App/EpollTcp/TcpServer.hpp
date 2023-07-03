#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include "Platform_Types.hpp"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <functional>
#include <fcntl.h>
typedef void (*RecvCallback)(sint32 clientfd,void* data,uint32 len);
typedef  std::function<void(sint32,void*,uint32)> StdRecvCallback;
class TcpServerBase
{
    
public:
    TcpServerBase(RecvCallback callback_in) : recv_callback(callback_in)
    {
        std::cout << "TcpServerBase constructor" << std::endl;
    }
    TcpServerBase(const TcpServerBase& other)            = delete;
    TcpServerBase& operator=(const TcpServerBase& other) = delete;
    TcpServerBase(TcpServerBase&& other)                 = delete;
    TcpServerBase& operator=(TcpServerBase&& other)      = delete;
    TcpServerBase()                                      = delete;

    virtual sint32 Create(void) = 0;
    virtual sint32 Accept(sint32 socketfd) = 0;
    virtual void Receive(void) = 0;

    virtual ~TcpServerBase()
    {
        std::cout << "TcpServerBase deconstructor " << std::endl;
    }
protected:
    const int MAX_LISTEN_NUM = 20;
    boolean Bind(int32_t sockfd, struct sockaddr *addr, uint32 addr_len);
    boolean Listen(sint32 sockfd, sint32 num);
    sint32 Send(int32_t clientfd, void *data, uint32 len);
    void Set_Nonblocking(sint32 sockfd);
    boolean Set_PortReuse(sint32 sockfd);
    void Close(sint32 sockfd);
    void Update(RecvCallback callback,sint32 clientfd,void *buff, uint32 len);
    RecvCallback recv_callback = nullptr;
};

#endif 


