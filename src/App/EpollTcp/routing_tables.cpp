/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/routing_tables.cpp
 * @Description: 
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-04 18:00:47
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "routing_tables.hpp"


routing_tables::routing_tables()
{
}

routing_tables::~routing_tables()
{
}

void routing_tables::register_client(sint32 clientfd,uint32 src_id)
{
    routing_tables_m.insert(std::make_pair(clientfd,src_id));
}

