#ifndef __MESSAGE_ACTION_BASE__
#define __MESSAGE_ACTION_BASE__

#include "message_action_host.hpp"
#include "routing_tables.hpp"
#include "message_handler.hpp"
class message_handler;
class LOGIN : public ACTION
{
public:
    LOGIN(const std::shared_ptr<routing_tables>& _routing_tables,const std::shared_ptr<message_handler>& _message_handler):routing_tables_m(_routing_tables),
                                                                                                                           message_handler_m(_message_handler)                                                   
    {
        std::cout << "LOGIN Constructor" << std::endl;
    }

    ~LOGIN() override
    {
        std::cout << "LOGIN Destructor" << std::endl;
    }

    void Do_Action(message_impl& msg) override;

private:
    std::shared_ptr<routing_tables> routing_tables_m;
    std::shared_ptr<message_handler> message_handler_m;
};

class LOGOUT : public ACTION
{
public:
    LOGOUT(const std::shared_ptr<routing_tables>& _routing_tables,const std::shared_ptr<message_handler>& _message_handler):routing_tables_m(_routing_tables),
                                                                                                                            message_handler_m(_message_handler)   
    {
        std::cout << "LOGOUT Constructor" << std::endl;
    }

    ~LOGOUT() override
    {
        std::cout << "LOGOUT Destructor" << std::endl;
    }

    void Do_Action(message_impl& msg) override;

private:
    std::shared_ptr<routing_tables> routing_tables_m;
    std::shared_ptr<message_handler> message_handler_m;
};

class CHECK : public ACTION
{
public:
    CHECK(const std::shared_ptr<routing_tables>& _routing_tables,const std::shared_ptr<message_handler>& _message_handler):routing_tables_m(_routing_tables),
                                                                                                                           message_handler_m(_message_handler)   
    {
        std::cout << "CHECK Constructor" << std::endl;
    }

    ~CHECK() override
    {
        std::cout << "CHECK deconstructor" << std::endl;
    }
    void Do_Action(message_impl& msg) override;

private:
    std::shared_ptr<routing_tables> routing_tables_m;
    std::shared_ptr<message_handler> message_handler_m;
};

class FORWARD : public ACTION
{
public:
    FORWARD(const std::shared_ptr<routing_tables>& _routing_tables,const std::shared_ptr<message_handler>& _message_handler):routing_tables_m(_routing_tables),
                                                                                                                             message_handler_m(_message_handler)   
    {
        std::cout << "FORWARD Constructor" << std::endl;
    }

    ~FORWARD() override
    {
        std::cout << "FORWARD deconstructor" << std::endl;
    }
    void Do_Action(message_impl& msg) override;

private:
    std::shared_ptr<routing_tables> routing_tables_m;
    std::shared_ptr<message_handler> message_handler_m;
};

class BROADCAST : public ACTION
{
public:
    BROADCAST(const std::shared_ptr<routing_tables>& _routing_tables,const std::shared_ptr<message_handler>& _message_handler):routing_tables_m(_routing_tables),
                                                                                                                               message_handler_m(_message_handler)   
    {
        std::cout << "BROADCAST Constructor" << std::endl;
    }

    ~BROADCAST() override
    {
        std::cout << "BROADCAST deconstructor" << std::endl;
    }

    void Do_Action(message_impl& msg) override;

private:
    std::shared_ptr<routing_tables> routing_tables_m;
    std::shared_ptr<message_handler> message_handler_m;
};


#endif