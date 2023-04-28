#ifndef __CONCRETE_OBSERVERD__HPP__
#define __CONCRETE_OBSERVERD__HPP__

#include <iostream>
#include <string>
#include "observer.hpp"
#include "spdlog/spdlog.h"
class ConcreteObserver_0 : public observer
{
public:
    ~ConcreteObserver_0();

    ConcreteObserver_0& operator=(const ConcreteObserver_0&) = delete;
    ConcreteObserver_0(const ConcreteObserver_0&) = delete;

    static ConcreteObserver_0* get_instance()
    {
        static ConcreteObserver_0 instance;
        return &instance;
    }

    void Notify(uint16_t DID, void* data,unsigned int len);
private:
    std::string m_name;
    ConcreteObserver_0()
    {
        m_name="ConcreteObserver";
        spdlog::info("ConcreteObserver default Constructor");
    }
};

#endif //