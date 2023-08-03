#include "message_header.hpp"

message_header::message_header()  : header(0u),
                                    src_id(0u),             /*Source identity*/
                                    dst_id(0u),              /*Destination id*/
                                    topic_id(0u),            /*topic identity*/
                                    cmd_id(_COM_CMD_TYPES_::COM_CMD_UNKNOWN),   /*com identity*/
                                    len(0u)                 /*remain len without header*/
{

};


message_header::message_header(const message_header& _header) : header(_header.header),
                                                                src_id(_header.src_id),        /*Source identity*/
                                                                dst_id(_header.dst_id),        /*Destination id*/
                                                                topic_id(_header.topic_id),    /*topic identity*/
                                                                cmd_id(_header.cmd_id),        /*com identity*/
                                                                len(_header.len)               /*remain len without header*/
{

};

message_header::~message_header()
{

};

boolean message_header::serialize(std::shared_ptr<serializer> _to) const
{
    return (0 != _to
            && _to->serialize(header)
            && _to->serialize(src_id)
            && _to->serialize(dst_id)
            && _to->serialize(topic_id)
            && _to->serialize((uint32)cmd_id)
            && _to->serialize(len));
}

boolean message_header::deserialize(std::shared_ptr<deserializer> _from)
{
    bool is_successful;

    is_successful = (0 != _from
            && _from->deserialize(header)
            && _from->deserialize(src_id)
            && _from->deserialize(dst_id)
            && _from->deserialize(topic_id)
            && _from->deserialize((uint32&)cmd_id)
            && _from->deserialize(len));

    return is_successful;
}