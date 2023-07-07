#ifndef _IPCSERVER_HPP_
#define _IPCSERVER_HPP_

#include "TcpServer.hpp"
#include "Message_Cfg.hpp"
#include <sys/un.h>
#include <string>
#include <cstring>
#include <vector>
#define _IPC_CLIENT_ sint32

/**
 * @brief 进程间通信服务器类
 * 实现Ipcserver的创建
 * 支持多客户端管理，通过回调函数获取客户端消息
 */
typedef std::function<void(sint32,void*,uint32)> RecvCallback;


class IPCServer : public TcpServerBase
{
public:
    IPCServer(RecvCallback StdRecvCallback_in,std::string ipcfile):ipcfile_m(ipcfile),
                                                                   StdRecvCallback(StdRecvCallback_in)
    {
        std::cout << "IPC Server Parameterized constructor:" << ipcfile << std::endl;
        Ipc_Startup();
    };

    /**
     * @brief Copy constructor
     */
    IPCServer(const IPCServer& other);

        /**
     * @brief move constructor
     */
    IPCServer(IPCServer&& other);
    IPCServer& operator=(const IPCServer& other) = delete;
    IPCServer& operator=(IPCServer&& other)      = delete;

    /**
     * @brief deconstructor
     */
    ~IPCServer() override;
    void AddIpcClient(sint32 clientfd);
    void DelIpcClient(sint32 clientfd);
    void SetIpcClientInfo(sint32 localfd,sint32 src_id,boolean linksta,_CLIENT_LINKWAY_TYPES_ linkway);
    sint32 Accept(sint32 socketfd) override;
public:
    sint32                                   un_sock_m; //ipcserver socket fd
    RecvCallback                             StdRecvCallback;//receive client message callback function
    std::vector<_CLIENT_INFO_>                      ipc_clients_m;//vector to save clients info
private:
    boolean Ipc_Init();
    boolean Ipc_Startup(void);
    sint32 Create(void) override;

    struct sockaddr_un un_addr_m; //ipc server address
    std::string ipcfile_m;        //ipc file
};

#endif