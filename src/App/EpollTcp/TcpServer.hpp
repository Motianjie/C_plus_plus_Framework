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
/**
 * @brief Tcp服务器基类，
 * 实现了通用的server操作如bind,listen,send,close
 * 实现了常用的设置socket属性，如设置非阻塞，设置端口复用
 * Create和Accept对于ipc和rpc实现上有差异，所以交给对应的子类实现，此处只留接口
 */
class TcpServerBase
{
    
public:
    /**
     * @brief 默认构造函数
     */
    TcpServerBase()
    {
        std::cout << "TcpServerBase constructor" << std::endl;
    }
    TcpServerBase(const TcpServerBase& other)            = delete;
    TcpServerBase& operator=(const TcpServerBase& other) = delete;
    TcpServerBase(TcpServerBase&& other)                 = delete;
    TcpServerBase& operator=(TcpServerBase&& other)      = delete;

    virtual sint32 Create(void) = 0;
    virtual sint32 Accept(sint32 socketfd) = 0;

    virtual ~TcpServerBase()
    {
        std::cout << "TcpServerBase deconstructor " << std::endl;
    }

    void Set_Nonblocking(sint32 sockfd);
    boolean Set_PortReuse(sint32 sockfd);

protected:
    boolean Bind(int32_t sockfd, struct sockaddr *addr, uint32 addr_len);
    boolean Listen(sint32 sockfd, sint32 num);
    sint32 Send(int32_t clientfd, void *data, uint32 len);
    void Close(sint32 sockfd);
    const int MAX_LISTEN_NUM = 20;//服务器Listen的最大socket个数
};

#endif 


