#include "TcpServer.hpp"

boolean TcpServerBase::Bind(sint32 sockfd, struct sockaddr *addr, uint32 addr_len)
{
    while(bind(sockfd,(struct sockaddr *)addr,(socklen_t)addr_len) == -1)
        {
            printf("unix socket bind error: %s",strerror(errno));
            return false;
        }
    return true;
}

boolean TcpServerBase::Listen(sint32 sockfd, sint32 num)
{
    while(listen(sockfd, num) == -1)
    {
        printf("unix socket listen error: %s",strerror(errno));
        return false;
    }

    return true;
}

sint32 TcpServerBase::Send(int32_t clientfd, void *data, uint32 len)
{
    int32_t numbytes = 0;
    int32_t ret;

    if(-1 == clientfd)
    {
        printf("client socket disconnect...");
        return -1;
    }

    if(NULL == data)
    {
        printf("null pointer!");
        return -1;
    }

    while(numbytes < (int32_t)len)
    {
        ret = send(clientfd, (char*)data+numbytes, (size_t)((ssize_t)len-numbytes), 0);
        if(ret == 0)
        {        
            printf("line discnnect");       
            return 0;
        }
        else if(ret == -1)
        { 
            if(errno == EINTR || errno == EAGAIN)
            {
                usleep(1000);
                continue;
            }

            printf("line discnnect");
            return 0;
        }
        else
        {
            numbytes += (int32_t)ret;
        }
    }
    printf("[D]sockfd[%d] send %d bytes!", clientfd, numbytes);
    return numbytes;
}

void TcpServerBase::Close(sint32 sockfd)
{
    if(close(sockfd) == 0) 
    {
        std::cout << "Socket closed successfully." << std::endl;
    }else 
    {
        std::cout << "Failed to close socket. Error code: " << errno << std::endl;
    }
}

void TcpServerBase::Set_Nonblocking(sint32 sockfd)
{
    int32_t old_option = fcntl( sockfd, F_GETFL );
    int32_t new_option = old_option | O_NONBLOCK;
    fcntl(sockfd,F_SETFL,new_option );
    return;   
}

boolean TcpServerBase::Set_PortReuse(sint32 sockfd)
{
    int reuse = 1; // 用于设置 SO_REUSEADDR 选项的值
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) 
    {
        std::cout << "Failed to set SO_REUSEADDR option." << std::endl;
        close(sockfd);
        return false;
    }
    return true;
}

void TcpServerBase::Update(RecvCallback callback,sint32 clientfd,void *buff, uint32 len)
{
    if(callback == nullptr)
    {
        std::cout << "callback is nullptr" << std::endl;
        return;
    }
    if(buff == nullptr)
    {
        std::cout << "buff is nullptr" << std::endl;
    }

    callback(clientfd,buff,len);
}
