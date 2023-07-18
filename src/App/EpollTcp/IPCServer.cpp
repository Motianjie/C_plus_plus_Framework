#include "IPCServer.hpp"
#include <algorithm>

IPCServer::IPCServer(const IPCServer& other)
{
    std::cout << "IPC Server copy constructor:"<< std::endl;
    un_sock_m = other.un_sock_m;
    StdRecvCallback = other.StdRecvCallback;
    un_addr_m = other.un_addr_m;
    ipcfile_m = other.ipcfile_m;
}

IPCServer::IPCServer(IPCServer&& other)
{
    std::cout<<"IPCServer move constructor " << std::endl;
    un_sock_m = other.un_sock_m;
    StdRecvCallback = other.StdRecvCallback;
    un_addr_m = other.un_addr_m;
    ipcfile_m = other.ipcfile_m;
}

/*============================================================================*/
/*  @brief      Create a ipc server socket
 *              Asynchronous and Non Reentrant
 *  @param
 *  @return
 *      @retval     ipc server socket fd
*/
/*============================================================================*/ 
sint32 IPCServer::Create(void)
{
    sint32 svr_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(svr_fd < 0)
    {
        std::cout << "Error creating ipc socket " << strerror(errno) << std::endl;
    }
    return svr_fd;
}


/*============================================================================*/
/*  @brief      copy ipc address to ipc server address
 *              Asynchronous and Non Reentrant
 *  @param
 *  @return
 *      @retval     false:copy failed
 *      @retval     true:copy succeeded
*/
/*============================================================================*/ 
boolean IPCServer::Ipc_Init()
{
    un_sock_m = -1;
    memset(&un_addr_m, 0u,sizeof(un_addr_m));
    un_addr_m.sun_family = AF_UNIX;
    if(!ipcfile_m.empty())
    {
        strncpy(un_addr_m.sun_path,ipcfile_m.c_str(),sizeof(un_addr_m.sun_path)-1);
    }  else
    {
        std::cout << "ipc file is empty" << std::endl;
        return false;
    }
    return true;
        
}

/*============================================================================*/
/*  @brief      Finish Ipc server settings
 *              Asynchronous and Non Reentrant
 *  @param
 *  @return
 *      @retval     false:set failed
 *      @retval     true:set succeeded
*/
/*============================================================================*/ 
boolean IPCServer::Ipc_Startup(void)
{
    boolean ret = false;
    ret = Ipc_Init();
    if(ret)
        un_sock_m = Create();
    else 
        return false;

    unlink(ipcfile_m.c_str());
    if(un_sock_m > 0)
    {
        Set_Nonblocking(un_sock_m);
        ret = Set_PortReuse(un_sock_m);
    }else
    {
        return false;
    }
        
    if(ret)
        ret = Bind(un_sock_m,(struct sockaddr *)&un_addr_m,(uint32)sizeof(un_addr_m));
    else
        return false;

    if(ret)
        ret = Listen(un_sock_m,MAX_LISTEN_NUM);
    else
        return false;

    return true;
}

/*============================================================================*/
/*  @brief      Accept ipc client connection
 *              Asynchronous and Non Reentrant
 *  @param
 *  @return
 *      @retval     client socket fd
*/
/*============================================================================*/ 
sint32 IPCServer::Accept(sint32 socketfd)
{
    sint32 clt_sock;
    struct sockaddr_un clt_addr;    
    uint32 addrLen = sizeof(struct sockaddr);

    while((clt_sock = accept(socketfd,(struct sockaddr*)&clt_addr,(socklen_t*)&addrLen)) < 0)
    {   
        return -1;
    }

    return clt_sock;
}

/*============================================================================*/
/*  @brief      Add client socket fd to ipc vector
 *              Asynchronous and Non Reentrant
 *  @param
 *  @return
 *      @retval     client socket fd
*/
/*============================================================================*/ 
void IPCServer::AddIpcClient(sint32 clientfd)
{
    _CLIENT_INFO_ clientinfo{};
    clientinfo.src_local_sockfd = clientfd;
    ipc_clients_m.push_back(clientinfo);
}

/*============================================================================*/
/*  @brief      Set client info by clientfd
                if ipc_client was accepted by ipc server,ipc server will add client fd in clients vector without other info
 *              Asynchronous and Non Reentrant
 *  @param
 *  @return
 *      @retval     
*/
/*============================================================================*/ 
void IPCServer::SetIpcClientInfo(sint32 clientfd,sint32 src_id,boolean linksta,_CLIENT_LINKWAY_TYPES_ linkway)
{
    auto it = std::find_if(ipc_clients_m.begin(), ipc_clients_m.end(),
    [&](const _CLIENT_INFO_& client){ return client.src_local_sockfd == clientfd;});//lambda 

    if(it != ipc_clients_m.end())
    {
        (*it).linksta = linksta;
        (*it).linkway = linkway;
        (*it).src_id = src_id;
        std::cout << "Set client fd " << (*it).src_local_sockfd << " info " << \
                    " src_id "        << (*it).src_id  << 
                    " linkway "       << (*it).linkway << 
                    " linksta "       << (*it).linksta << std::endl;
    }else
    {
        std::cout << "client fd " << clientfd << " not found" << std::endl;
    }
}

/*============================================================================*/
/*  @brief      Delete client socket fd to ipc vector
 *              Asynchronous and Non Reentrant
 *  @param
 *  @return
 *      @retval     client socket fd
*/
/*============================================================================*/ 
void IPCServer::DelIpcClient(sint32 clientfd)
{
    // auto it = std::find(ipc_clients_m.begin(), ipc_clients_m.end(), clientfd);
    auto it = std::find_if(ipc_clients_m.begin(), ipc_clients_m.end(),
    [&](const _CLIENT_INFO_ client){ return client.src_local_sockfd == clientfd;});
    if(it != ipc_clients_m.end())
    {
        std::cout << "Delete client fd " << (*it).src_local_sockfd << std::endl;
        ipc_clients_m.erase(it);
    }

    for (auto ipc_client : ipc_clients_m)
    {
        std::cout << "Current ipc server " << un_sock_m <<  " ipc clients " << ipc_client.src_local_sockfd << std::endl;
    }
}

IPCServer::~IPCServer()
{
    std::cout << "IPC Server destructor" << std::endl;
}

