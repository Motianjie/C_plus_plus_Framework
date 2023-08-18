#include "message_action_impl.hpp"


message_action_impl::message_action_impl(const std::shared_ptr<routing_tables>& _routing_tables,const std::shared_ptr<message_handler>& _message_handler)
{
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_LOGIN,std::make_unique<LOGIN>(_routing_tables,_message_handler));
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_LOGOUT,std::make_unique<LOGOUT>(_routing_tables,_message_handler));
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_CHECK,std::make_unique<CHECK>(_routing_tables,_message_handler));
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_FORWARD,std::make_unique<FORWARD>(_routing_tables,_message_handler));
    actionmap_m.emplace(_COM_CMD_TYPES_::COM_CMD_BROADCAST,std::make_unique<BROADCAST>(_routing_tables,_message_handler));
}