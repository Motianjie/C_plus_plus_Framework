#include "message_header.hpp"

message_header::message_header()  : header_m(0u),
                                    src_id_m(0u),             /*Source identity*/
                                    dst_id_m(0u),              /*Destination id*/
                                    topic_id_m(0u),            /*topic identity*/
                                    cmd_id_m(_COM_CMD_TYPES_::COM_CMD_UNKNOWN),   /*com identity*/
                                    len_m(0u)                 /*remain len without header*/
{

}


message_header::message_header(const message_header& _header) : header_m(_header.header_m),
                                                                src_id_m(_header.src_id_m),        /*Source identity*/
                                                                dst_id_m(_header.dst_id_m),        /*Destination id*/
                                                                topic_id_m(_header.topic_id_m),    /*topic identity*/
                                                                cmd_id_m(_header.cmd_id_m),        /*com identity*/
                                                                len_m(_header.len_m)               /*remain len without header*/
{

}

 message_header::message_header(const header_t &header_,\
                   const src_id_t &src_id_,\
                   const dst_id_t &dst_id_,\
                   const topic_id_t & topic_id_,\
                   const _COM_CMD_TYPES_& cmd_id_,\
                   const len_t & len_)
                   
                   :header_m(header_),
                    src_id_m(src_id_),
                    dst_id_m(dst_id_),   
                    topic_id_m(topic_id_),
                    cmd_id_m(cmd_id_),
                    len_m(len_)    
{

}

message_header::~message_header()
{

}

boolean message_header::serialize(std::shared_ptr<serializer> _to) const
{
    return (0 != _to
            && _to->serialize(header_m)
            && _to->serialize(src_id_m)
            && _to->serialize(dst_id_m)
            && _to->serialize(topic_id_m)
            && _to->serialize((uint32)cmd_id_m)
            && _to->serialize(len_m));
}

boolean message_header::deserialize(std::shared_ptr<deserializer> _from)
{
    bool is_successful;

    is_successful = (0 != _from
            && _from->deserialize(header_m)
            && _from->deserialize(src_id_m)
            && _from->deserialize(dst_id_m)
            && _from->deserialize(topic_id_m)
            && _from->deserialize((uint32&)cmd_id_m)
            && _from->deserialize(len_m));

    return is_successful;
}


void message_header::set_header(const header_t & header_)
{
    header_m = header_;
}

void message_header::set_src_id(const src_id_t & src_id_)
{
    src_id_m = src_id_;
}

void message_header::set_dst_id(const dst_id_t & dst_id_)
{
    dst_id_m = dst_id_;
}

void message_header::set_topic_id(const topic_id_t & topic_id_)
{
    topic_id_m = topic_id_;
}

void message_header::set_cmd_id(const _COM_CMD_TYPES_& cmd_id_)
{
    cmd_id_m = cmd_id_;
}

void message_header::set_len(const len_t & len_)
{
    len_m = len_;
}