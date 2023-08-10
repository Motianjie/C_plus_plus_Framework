/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/routing_tables.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-10 14:17:27
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __ROUTING_TABLES__
#define __ROUTING_TABLES__
#include "Platform_Types.hpp"
#include <unordered_map>
class routing_tables
{

public:
    routing_tables();
    ~routing_tables();

    void Register(sint32 clientfd,uint32 src_id);
    void Unregister(sint32 clientfd);
    void Unregister(uint32 src_id);

    
    boolean routing_map(sint32 dst_id,sint32& clientfd);
private:
    std::unordered_map<sint32,uint32> routing_tables_m;
};


   




#endif