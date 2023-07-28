/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/Message_Cfg.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-07-28 17:26:24
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef _MESSAGE_CFG_HPP_
#define _MESSAGE_CFG_HPP_
#include "Platform_Types.hpp"
/* communication request command*/

typedef enum 
{
    COM_CMD_LOGIN = 1,
    COM_CMD_LOGOUT,   
    COM_CMD_CHECK,      /*get connected to COM server tasks type*/ 
    COM_CMD_FORWARD,    /*forward srcTask data to destTask*/     
    COM_CMD_BROADCAST,   /*broadcast srcTask data to every tasks*/  
    COM_CMD_MAX,
}_COM_CMD_TYPES_;

typedef enum 
{
    LINKWAY_IPC = 1,
    LINKWAY_RPC,
    LINKWAY_MAX,    
}_CLIENT_LINKWAY_TYPES_;

typedef struct
{
    uint8 header ;
    uint32 src_id;              /*Source identity*/
    uint32 dst_id;              /*Destination id*/
    uint32 topic_id;            /*topic identity*/
    _COM_CMD_TYPES_ cmd_id;     /*com identity*/
    uint64 len;                 /*remain len without header*/
}ALIGN_4BYTES _COM_HEADER_INFO_;

typedef struct
{
    _COM_HEADER_INFO_ com_header; /*header/
    uint8* data;                  /*data ptr*/
    uint32 datelen;               /*data's len*/
}ALIGN_4BYTES _COM_MESSAGE_INFO_;

typedef struct
{
    sint32 src_id;              /*Source identity*/
    sint32 src_local_sockfd;    /*Local socket of client*/
    boolean linksta;            /*true:link up false:link down*/
    _CLIENT_LINKWAY_TYPES_ linkway;             
}ALIGN_4BYTES _CLIENT_INFO_;




#endif