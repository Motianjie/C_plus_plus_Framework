#ifndef _IPCSERVER_HPP_
#define _IPCSERVER_HPP_

#include "TcpServer.hpp"
#include <sys/un.h>
#include <string>
#include <cstring>
class IPCServer : public TcpServerBase
{
public:
    IPCServer(RecvCallback callback_in,std::string ipcfile):TcpServerBase(callback_in),
                                                            ipcfile_m(ipcfile)
    {
        std::cout << "IPC Server constructor:" << ipcfile << std::endl;
        Ipc_Startup();
    };
    IPCServer(const IPCServer& other)            = delete;
    IPCServer& operator=(const IPCServer& other) = delete;
    IPCServer(IPCServer&& other)                 = delete;
    IPCServer& operator=(IPCServer&& other)      = delete;

    virtual ~IPCServer();
protected:
    sint32 Accept(sint32 socketfd) override;
    virtual void Receive(void);
    struct sockaddr_un un_addr_m;
    sint32             un_sock_m;
    std::string ipcfile_m;
private:
    boolean Ipc_Init();
    boolean Ipc_Startup(void);
    sint32 Create(void) override;
};

#endif