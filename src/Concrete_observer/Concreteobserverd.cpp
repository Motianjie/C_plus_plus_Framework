#include "Concreteobserverd.hpp"
#include <iostream>

ConcreteObserver_0::~ConcreteObserver_0()
{
    std::cout << "ConcreteObserver destructor " << m_name << std::endl;
}

void ConcreteObserver_0::Notify(uint16_t DID,void* data,unsigned int len)
{
    std::cout << "Concrete name " << ConcreteObserver_0::GetName() << " " <<
    "Notify len " << len << " Notify data " << data << " " << "DID " << DID << std::endl;
}

std::string ConcreteObserver_0::GetName(void)
{
    return m_name;
}