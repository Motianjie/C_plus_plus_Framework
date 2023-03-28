#include <iostream>
#include "Concrete_subject.hpp"

void ConcreteSubject_0::RegisterSuject(uint16_t DID,observer* pobserver)
{
    if(SOA_TYPE_MAX <= DID)
    {
        std::cout << "Func[" << __FUNCTION__ << "]" << "DID over range" << std::endl;
        return;
    }
    this->Soamap[DID].push_back(pobserver);
    // m_observerslist.push_back(pobserver);
}

void ConcreteSubject_0::UnregisterSuject(uint16_t DID,observer* pobserver)
{
    m_observerslist.remove(pobserver);
}

void ConcreteSubject_0::Notify(uint16_t DID ,void* data,unsigned int len)
{
    if(data != NULL && len > 0u)
    {
        if(DID < SOA_TYPE_MAX)
        {
            for(auto it = this->Soamap[DID].begin();it != this->Soamap[DID].end();it++)
            {
                (*it)->Notify(DID,data,len);
            }
        }
    } 
}
