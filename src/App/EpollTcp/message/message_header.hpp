/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_header.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-17 15:45:20
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __MESSAGE_HEADER__
#define __MESSAGE_HEADER__
#include "Platform_Types.hpp"
#include <memory>
#include "Message_Cfg.hpp"
#include "serializer.hpp"
#include "deserializer.hpp"
#include "spdlog/spdlog.h"

class serializer;
class deserializer;

class message_header
{
public:
    message_header();
    message_header(const message_header& _header);
    message_header(const header_t &header_,\
                   const cnt_t &cnt_,\
                   const src_id_t &src_id_,\
                   const dst_id_t &dst_id_,\
                   const topic_id_t & topic_id_,\
                   const _COM_CMD_TYPES_& cmd_id_,\
                   const len_t & len_);
    ~message_header();

    /**
     * @description: 进程间通信头部序列化
     * @param {shared_ptr<serializer>} _to 序列化器
     * @return {true: serialize success, false: serialize failure}
     */    
    boolean serialize(std::shared_ptr<serializer> _to) const;
    /**
     * @description: 进程间通信头部反序列化
     * @param {shared_ptr<deserializer>} _from 反序列化器
     * @return {true: deserialize success, false: deserialize failure}
     */    
    boolean deserialize(std::shared_ptr<deserializer> _from);
    void set_header(const header_t & header_);
    void set_cnt(const cnt_t & cnt_);
    void set_src_id(const src_id_t & src_id_);
    void set_dst_id(const dst_id_t & dst_id_);
    void set_topic_id(const topic_id_t & topic_id_);
    void set_cmd_id(const _COM_CMD_TYPES_& cmd_id_);
    void set_len(const len_t & len_);

    header_t get_header() const;
    cnt_t get_cnt()const;
    src_id_t get_src_id() const;
    dst_id_t get_dst_id() const;
    topic_id_t get_topic_id() const;
    _COM_CMD_TYPES_ get_cmd_id() const;
    len_t get_len() const;
    
    void show_header() const
    { 
        #ifdef DEBUG  
        spdlog::info
        (
            "Show Recv message_header header[0x{:02x}] cnt[0x{:02x}] src_id[0x{:02x}] dst_id[0x{:02x}] topic_id[0x{:02x}] cmd_id[0x{:02x}] len[0x{:02x}]",
            header_m,
            cnt_m,
            src_id_m,
            dst_id_m,
            topic_id_m,
            cmd_id_m,
            len_m
        );
        #endif
    }

private:
    header_t header_m ;             /*进程间通信头部标识符#$%& 0x23 0x24 0x25 0x26*/
    cnt_t    cnt_m ;
    src_id_t src_id_m;              /*Source identity*/
    dst_id_t dst_id_m;              /*Destination id*/
    topic_id_t topic_id_m;            /*topic identity*/
    _COM_CMD_TYPES_ cmd_id_m;     /*com identity*/
    len_t len_m;                 /*remain len without header*/
};

#endif