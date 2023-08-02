#ifndef __MESSAGE_IMPL__
#define __MESSAGE_IMPL__


#include "Message_Cfg.hpp"
#include "message_header.hpp"

class message_impl
{
public:
    message_impl();

    ~message_impl();

    boolean serialize(serializer *_to) const;
    boolean deserialize(deserializer *_from);

public:
    message_header message_header_m;
    uint32 len_m;
    std::vector<uint8> data_m;

};

#endif