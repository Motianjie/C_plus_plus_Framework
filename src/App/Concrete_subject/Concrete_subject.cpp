/*
 * @FilePath: /C_plus_plus_Framework/src/App/Concrete_subject/Concrete_subject.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-09 16:21:11
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
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
    this->Soamap[DID].remove_if([&](const std::weak_ptr<Observer>& o) { return o.lock() == pobserver; });
}

void ConcreteSubject_0::Notify(uint16_t DID ,void* data,unsigned int len)
{
    if(data != NULL && len > 0u && DID < SOA_TYPE_MAX)
    {
        for(auto it : this->Soamap[DID])
        {
            if (auto observerPtr = it.lock())
                observerPtr->Notify(DID,data,len);
        }
    } 
}
