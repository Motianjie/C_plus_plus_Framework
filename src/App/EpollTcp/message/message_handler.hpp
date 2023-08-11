#ifndef __message_handler__
#define __message_handler__

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <deque>
#include <functional>
#include "Message_Cfg.hpp"
#include "spdlog/spdlog.h"
#include "message_header.hpp"
#include "message_impl.hpp"
class message_impl;
typedef std::function<void(const message_impl& message)> MessageCallback;
class ACTION
{
public:
    ACTION()
    {
        std::cout << "Action constructor" << std::endl;
    }

    virtual ~ACTION()
    {
        std::cout << "Action deconstructor" << std::endl;
    }
    virtual void Do_Action(message_impl& msg,MessageCallback mesgcbk) = 0;
    
};

class LOGIN : public ACTION
{
public:
    LOGIN()
    {
        std::cout << "LOGIN Constructor" << std::endl;
    }

    ~LOGIN() override
    {
        std::cout << "LOGIN Destructor" << std::endl;
    }

    void Do_Action(message_impl& msg,MessageCallback mesgcbk) override;
};

class LOGOUT : public ACTION
{
public:
    LOGOUT()
    {
        std::cout << "LOGOUT Constructor" << std::endl;
    }

    ~LOGOUT() override
    {
        std::cout << "LOGOUT Destructor" << std::endl;
    }

    void Do_Action(message_impl& msg,MessageCallback mesgcbk) override;
};

class CHECK : public ACTION
{
public:
    CHECK()
    {
        std::cout << "CHECK Constructor" << std::endl;
    }

    ~CHECK() override
    {
        std::cout << "CHECK deconstructor" << std::endl;
    }
    void Do_Action(message_impl& msg,MessageCallback mesgcbk) override;
};

class FORWARD : public ACTION
{
public:
    FORWARD()
    {
        std::cout << "FORWARD Constructor" << std::endl;
    }

    ~FORWARD() override
    {
        std::cout << "FORWARD deconstructor" << std::endl;
    }
    void Do_Action(message_impl& msg,MessageCallback mesgcbk) override;
};

class BROADCAST : public ACTION
{
public:
    BROADCAST()
    {
        std::cout << "BROADCAST Constructor" << std::endl;
    }

    ~BROADCAST() override
    {
        std::cout << "BROADCAST deconstructor" << std::endl;
    }

    void Do_Action(message_impl& msg,MessageCallback mesgcbk) override;
};

class message_handler
{
public:
    message_handler();
    
    ~message_handler()
    {
        std::cout << "message_handler deconstructed" << std::endl;
        // message_handler_thread_m.join();   
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
            iter->second.Do_Action(msg,action_cbk);
        }
        else
        {
            spdlog::error("Com cmd type [{:d}] valid! ", com_cmd_types);
            return false;
        }
        return true;
    };

    void put_message(const message_impl& message);
    void put_message_out(const message_impl& message);
    void message_handle();
    void message_handler_thread();

    boolean pop_message(message_impl& mesg);

private:
    LOGIN login_m;
    LOGOUT logout_m;
    FORWARD forward_m;
    BROADCAST broadcast_m;
    CHECK check_m;
    std::map<const _COM_CMD_TYPES_, ACTION &> actionmap_m;

    std::deque<message_impl> message_deque_in_m;
    std::condition_variable message_deque_in_condition;
    std::mutex message_deque_in_mutex;

    std::deque<message_impl> message_deque_out_m;
    std::mutex message_deque_out_mutex;
    std::thread message_handler_thread_m;

    message_impl message_m;
    MessageCallback action_cbk;

};

#endif