#ifndef __MESGHANDLER__
#define __MESGHANDLER__

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include "Message_Cfg.hpp"
#include "spdlog/spdlog.h"
class ACTION
{
    public:
    ACTION()
    {
        std::cout<<"Action constructor"<<std::endl;
    }

    virtual ~ACTION()
    {

    }

    virtual void Do_Action() = 0;
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

    void Do_Action() override
    {
        std::cout << "LOGIN action" << std::endl;
    }
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

    void Do_Action() override
    {
        std::cout << "LOGOUT action" << std::endl;
    }
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
    void Do_Action() override
    {
        std::cout << "CHECK action" << std::endl;
    }
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
    void Do_Action() override
    {
        std::cout << "FORWARD action" << std::endl;
    }
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

    void Do_Action() override
    {
        std::cout << "BROADCAST action" << std::endl;
    }
};


class MesgHandler
{
    public:
    MesgHandler()
    {
        actionmap_m.emplace(COM_CMD_LOGIN,login_m);
        actionmap_m.emplace(COM_CMD_LOGOUT,logout_m);
        actionmap_m.emplace(COM_CMD_CHECK,check_m);
        actionmap_m.emplace(COM_CMD_FORWARD,forward_m);
        actionmap_m.emplace(COM_CMD_BROADCAST,broadcast_m);
    }
    ~MesgHandler()
    {
        std::cout << "MesgHandler deconstructed" << std::endl;
    }

    boolean MesgHandler_Action(_COM_CMD_TYPES_ com_cmd_types)
    {
        auto iter = actionmap_m.find(com_cmd_types);
        if(iter != actionmap_m.end())
        {
            iter->second.Do_Action();
        }else
        {
            spdlog::error("Com cmd type [{:d}] valid! ",com_cmd_types);
        }
    };
    
    private:
    LOGIN login_m;
    LOGOUT logout_m;
    FORWARD forward_m;
    BROADCAST broadcast_m;
    CHECK check_m;
    std::map<const _COM_CMD_TYPES_,ACTION&> actionmap_m;
};

#endif