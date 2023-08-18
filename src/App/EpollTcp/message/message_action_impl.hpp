/*
 * @FilePath: /C_plus_plus_Framework/src/App/EpollTcp/message/message_action_impl.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-17 15:29:27
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __MESSAGE_ACTION_IMPL__
#define __MESSAGE_ACTION_IMPL__

#include "message_action_base.hpp"
#include "message_action_host.hpp"
#include <map>
class LOGIN;
class LOGOUT;
class CHECK;
class FORWARD;
class BROADCAST;

class message_action_impl
{
    public:
    message_action_impl(const std::shared_ptr<routing_tables>& _routing_tables,const std::shared_ptr<message_handler>& _message_handler);
    ~message_action_impl()
    {
        
    }

        /**
     * @description: accoring to com_cmd_types and do action
     * @param {_COM_CMD_TYPES_} com_cmd_types
     * @return {true: action succeeded 
     *          false: action failed}
     */    
    boolean action(const _COM_CMD_TYPES_ com_cmd_types,message_impl& msg)
    {
        auto iter = actionmap_m.find(com_cmd_types);
        if (iter != actionmap_m.end())
        {
            if(iter->second.get())
                iter->second->Do_Action(msg);
            else
                spdlog::error("func{} line{} action faile",__FUNCTION__, __LINE__);
        }
        else
        {
            spdlog::error("Com cmd type [{:d}] valid! ", com_cmd_types);
            return false;
        }
        return true;
    };

    private:
    std::map<const _COM_CMD_TYPES_, std::unique_ptr<ACTION>> actionmap_m;
};

#endif