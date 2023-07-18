#include "Concreteobserverd.hpp"
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"
        

ConcreteObserver_0::~ConcreteObserver_0()
{
    spdlog::info("ConcreteObserver destructor");
}

void ConcreteObserver_0::Notify(uint16_t DID,void* data,unsigned int len)
{
    if(data != NULL && len > 0)
    {
        std::vector<uint8_t> buff;
        for(uint8_t i = 0; i < len;i++)
        {
            buff.push_back(*((uint8_t*)data+i));
        }
        
        spdlog::info("Func[{}] ConcreteName[{}] Notifylen[{}] DID[{}] data[{}]",
        __FUNCTION__,
        this->m_name,
        len,
        DID,
        spdlog::to_hex(buff));
    } 
}