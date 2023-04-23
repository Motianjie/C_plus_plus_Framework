#ifndef __CONCRETE_OBSERVERD__HPP__
#define __CONCRETE_OBSERVERD__HPP__

#include <iostream>
#include <string>
#include "observer.hpp"
#include "spdlog/spdlog.h"
class ConcreteObserver_0 : public observer
{
public:
    ConcreteObserver_0(std::string name):m_name(name)
    {
        spdlog::info("ConcreteObserver Constructor");
    }
    ~ConcreteObserver_0();

    void Notify(uint16_t DID, void* data,unsigned int len);

    std::string GetName(void);
private:
    std::string m_name;
};

#endif //