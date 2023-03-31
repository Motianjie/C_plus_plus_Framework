#include "Concreteobserverd.hpp"
#include <iostream>

ConcreteObserver_0::~ConcreteObserver_0()
{
    std::cout << "ConcreteObserver destructor " << m_name << std::endl;
}

void ConcreteObserver_0::Notify(uint16_t DID,void* data,unsigned int len)
{
    if(data != NULL && len > 0)
    {
        std::cout << "Notify DID " << DID << " ConcreteName:" << ConcreteObserver_0::GetName() <<
        " Notifylen:" << len << " Notify data:" << data << std::endl;
    } 
}

std::string ConcreteObserver_0::GetName(void)
{
    return m_name;
}