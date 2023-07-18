#include "Concreteobserverd_sample1.hpp"
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"
        

ConcreteObserver_sample_1::~ConcreteObserver_sample_1()
{
    spdlog::info("[{}] destructor",this->m_name);
}

void ConcreteObserver_sample_1::Notify(uint16_t DID,void* data,unsigned int len)
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