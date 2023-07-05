#include "IPCServer.hpp"

sint32 IPCServer::Create(void)
{
    sint32 svr_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(svr_fd < 0)
    {
        std::cout << "Error creating ipc socket " << strerror(errno) << std::endl;
    }
    return svr_fd;
}

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

void IPCServer::AddIpcClient(sint32 clientfd)
{
    ipc_clients_m.push_back(clientfd);
}

IPCServer::~IPCServer()
{
    unlink(ipcfile_m.c_str());
}

