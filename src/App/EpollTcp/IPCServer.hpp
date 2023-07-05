#ifndef _IPCSERVER_HPP_
#define _IPCSERVER_HPP_

#include "TcpServer.hpp"
#include <sys/un.h>
#include <string>
#include <cstring>
#include <vector>
#define _IPC_CLIENT_ sint32
class IPCServer : public TcpServerBase
{
public:
    IPCServer(std::function<void(sint32,void*,uint32)> StdRecvCallback_in,std::string ipcfile):ipcfile_m(ipcfile),
                                                                                               StdRecvCallback(StdRecvCallback_in)
    {
        std::cout << "IPC Server constructor:" << ipcfile << std::endl;
        Ipc_Startup();
    };
    // IPCServer(const IPCServer& other)            = delete;
    // IPCServer& operator=(const IPCServer& other) = delete;
     IPCServer(IPCServer&& other)
     {
        un_sock_m = other.un_sock_m;
        StdRecvCallback = other.StdRecvCallback;
        un_addr_m = other.un_addr_m;
        ipcfile_m = other.ipcfile_m;
     };
    // IPCServer& operator=(IPCServer&& other)      = delete;

    ~IPCServer();
    void AddIpcClient(sint32 clientfd);
    sint32 Accept(sint32 socketfd) override;
public:
    sint32             un_sock_m;
    std::function<void(sint32,void*,uint32)> StdRecvCallback;
        std::vector<sint32> ipc_clients_m;
private:
    boolean Ipc_Init();
    boolean Ipc_Startup(void);
    sint32 Create(void) override;

    struct sockaddr_un un_addr_m;
    std::string ipcfile_m;
    
    
};

#endif