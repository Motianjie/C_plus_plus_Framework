/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/routing_tables.cpp
 * @Description: 
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-10 16:13:49
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "routing_tables.hpp"
#include "spdlog/spdlog.h"

routing_tables::routing_tables()
{
}

routing_tables::~routing_tables()
{
}

void routing_tables::Register(sint32 clientfd,uint32 src_id)
{
    for(const auto& pair : routing_tables_m)
    {
        if(pair.second == src_id)
        {
            spdlog::warn("src_id[0x{:02x}] is already login",src_id);
            return;
        }
    }
    routing_tables_m.insert(std::make_pair(clientfd,src_id));
    spdlog::info("src_id[0x{:02x}] clientfd[0x{:02x}]",src_id,clientfd);
}

void routing_tables::Unregister(sint32 clientfd)
{
    if(routing_tables_m.count(clientfd) > 0)
    {
        spdlog::info("src_id[0x{:02x}] logout",routing_tables_m[clientfd]);
        routing_tables_m.erase(clientfd);
    }else
    {
        spdlog::warn("clientfd[0x{:02x}] is already logout",clientfd);
    }
}

void routing_tables::Unregister(uint32 src_id)
{
    for(const auto& pair : routing_tables_m)
    {
        if(pair.second == src_id)
        {
            routing_tables_m.erase(pair.first);
            return;
        }
    }
    spdlog::warn("src_id[0x{:02x}] is already logout",src_id);
}

boolean routing_tables::routing_map(sint32 dst_id,sint32& clientfd)
{
    for(const auto& pair : routing_tables_m)
    {
        if(pair.second == dst_id)
        {
            clientfd = pair.first;
            return true;
        }
    }
    return false;
}
