#include "TcpServer.hpp"

/*============================================================================*/
/*  @brief      Bind socket
 *              Asynchronous and Non Reentrant
 *  @param
 *      sint32 sockfd
 *  @return
 *      @retval     false:bind failed
 *      @retval     true:bind succeeded
*/
/*============================================================================*/ 
boolean TcpServerBase::Bind(sint32 sockfd, struct sockaddr *addr, uint32 addr_len)
{
    while(bind(sockfd,(struct sockaddr *)addr,(socklen_t)addr_len) == -1)
    {
        std::cout << "unix socket bind error: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

/*============================================================================*/
/*  @brief      Listen socket
 *              Asynchronous and Non Reentrant
 *  @param
 *      sint32 sockfd
 * @param
 *      sint32 num
 *  @return
 *      @retval     false:listen failed
 *      @retval     true:listen succeeded
*/
/*============================================================================*/ 
boolean TcpServerBase::Listen(sint32 sockfd, sint32 num)
{
    while(listen(sockfd, num) == -1)
    {
        std::cout << "unix socket listen error: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

/*============================================================================*/
/*  @brief      Send message through socket
 *              Asynchronous and Non Reentrant
 *  @param
 *      sint32 clientfd
 * @param
 *      void* data
 * @param
 *      uint32 len
 *  @return
 *      @retval     successful send numsbytes
*/
/*============================================================================*/ 
sint32 TcpServerBase::Send(sint32 clientfd, void *data, uint32 len)
{
    int32_t numbytes = 0;
    int32_t ret;

    if(-1 == clientfd)
    {
        std::cout << "client socket disconnect..." << std::endl;
        return -1;
    }

    if(NULL == data)
    {
        std::cout << "null pointer!" << std::endl;
        return -1;
    }

    while(numbytes < (sint32)len)
    {
        ret = send(clientfd, (char*)data+numbytes, (size_t)((ssize_t)len-numbytes), 0);
        if(ret == 0)
        {        
            std::cout << "line discnnect" << std::endl;       
            return 0;
        }
        else if(ret == -1)
        { 
            if(errno == EINTR || errno == EAGAIN)
            {
                usleep(1000);
                continue;
            }
            std::cout << "line discnnect" << std::endl;
            return 0;
        }
        else
        {
            numbytes += (sint32)ret;
        }
    }
    std::cout << "sockfd: " << clientfd << " send " << numbytes << " bytes " << std::endl;
    return numbytes;
}

/*============================================================================*/
/*  @brief      Close exited socket
 *              Asynchronous and Non Reentrant
 *  @param
 *      sint32 sockfd
 *  @return
 *      @retval     none
*/
/*============================================================================*/ 
void TcpServerBase::Close(sint32 sockfd)
{
    if(close(sockfd) == 0) 
    {
        std::cout << "Socket fd " << sockfd << " closed successfully." << std::endl;
    }else 
    {
        std::cout << "Failed to close socket. Error code: " << strerror(errno) << std::endl;
    }
}

/*============================================================================*/
/*  @brief      Set socket parameters to non-blocking mode
 *              Asynchronous and Non Reentrant
 *  @param
 *      sint32 sockfd
 *  @return
 *      @retval     none
*/
/*============================================================================*/ 
void TcpServerBase::Set_Nonblocking(sint32 sockfd)
{
    int32_t old_option = fcntl( sockfd, F_GETFL );
    int32_t new_option = old_option | O_NONBLOCK;
    fcntl(sockfd,F_SETFL,new_option );
    return;   
}

/*============================================================================*/
/*  @brief      Set socket parameters port reuse
 *              Asynchronous and Non Reentrant
 *  @param
 *      sint32 sockfd
 *  @return
 *      @retval     false:set failed
 *      @retval     true:set succeeded
*/
/*============================================================================*/ 
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
