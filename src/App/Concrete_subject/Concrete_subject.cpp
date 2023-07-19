#include <iostream>
#include "Concrete_subject.hpp"

ConcreteSubject_0::~ConcreteSubject_0()
{
    spdlog::info("[{}] destructor",this->m_name);
};

void ConcreteSubject_0::RegisterSuject(uint16_t DID,const std::shared_ptr<Observer>& pobserver)
{
    if(SOA_TYPE_MAX <= DID || pobserver == nullptr)
    {
        spdlog::info("Func[{:s}] Line[{:d}] DID over range or nullptr",__FUNCTION__,__LINE__);
        return;
    }
    
    this->Soamap[DID].push_back(pobserver);
}

void ConcreteSubject_0::UnregisterSuject(uint16_t DID,const std::shared_ptr<Observer>& pobserver)
{
    if(SOA_TYPE_MAX <= DID || pobserver == nullptr)
    {
        spdlog::info("Func[{:s}] Line[{:d}] DID over range or nullptr",__FUNCTION__,__LINE__);
        return;
    }
    this->Soamap[DID].remove(pobserver);
}

void ConcreteSubject_0::Notify(uint16_t DID ,void* data,unsigned int len)
{
    if(data != NULL && len > 0u && DID < SOA_TYPE_MAX)
    {
        for(auto it : this->Soamap[DID])
        {
            it->Notify(DID,data,len);
        }
    } 
}
