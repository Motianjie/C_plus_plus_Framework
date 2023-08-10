/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/Message_Cfg.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-10 15:03:31
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef _MESSAGE_CFG_HPP_
#define _MESSAGE_CFG_HPP_
#include "Platform_Types.hpp"
/* communication request command*/

#define MESSAGE_HEADER 0x23242526

typedef uint32 header_t;
typedef uint32 src_id_t;
typedef uint32 dst_id_t;
typedef uint32 topic_id_t;  
typedef uint32 len_t;



typedef enum 
{
    LINKWAY_IPC = 1,
    LINKWAY_RPC,
    LINKWAY_MAX,    
}_CLIENT_LINKWAY_TYPES_;

enum class _COM_CMD_TYPES_
{
    COM_CMD_LOGIN = 1,
    COM_CMD_LOGOUT,   
    COM_CMD_CHECK,      /*get connected to COM server tasks type*/ 
    COM_CMD_FORWARD,    /*forward srcTask data to destTask*/     
    COM_CMD_BROADCAST,   /*broadcast srcTask data to every tasks*/  
    COM_CMD_MAX,
    COM_CMD_UNKNOWN = 255, /*unknown*/
};

enum class _LOGIN_TOPIC_TYPE_ 
{
    _COM_CMD_LOGIN_TOPIC_REQ = 0,
    _COM_CMD_LOGIN_TOPIC_ACK,
};

enum class _IPC_ID_
{
    _COM_SERVER_ = 1,
    _COM_CLIENT_1_ = 2,
    _COM_CLIENT_2_ = 3,
    _COM_CLIENT_3_ = 4,
    _COM_CLIENT_4_ = 5,
    _COM_CLIENT_5_ = 6,
};



typedef struct
{
    sint32 src_id;              /*Source identity*/
    sint32 src_local_sockfd;    /*Local socket of client*/
    boolean linksta;            /*true:link up false:link down*/
    _CLIENT_LINKWAY_TYPES_ linkway;             
}ALIGN_4BYTES _CLIENT_INFO_;




#endif