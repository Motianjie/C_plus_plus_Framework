#ifndef __CONCRETE_OBSERVERD__HPP__
#define __CONCRETE_OBSERVERD__HPP__

#include <iostream>
#include <string>
#include "observer.hpp"
#include "spdlog/spdlog.h"
class ConcreteObserver_0 : public Observer
{
public:
    ~ConcreteObserver_0();
    static std::shared_ptr<ConcreteObserver_0> get_instance()
    {
        static std::shared_ptr<ConcreteObserver_0> instance(new ConcreteObserver_0());
        return instance;
    }
    void Notify(uint16_t DID, void* data,unsigned int len);

private:
    ConcreteObserver_0()
    {
        m_name="ConcreteObserver";
        spdlog::info("[{}] default Constructor",this->m_name);
    }
    ConcreteObserver_0& operator=(const ConcreteObserver_0&) = delete;
    ConcreteObserver_0(const ConcreteObserver_0&) = delete;
private:
    std::string m_name;
};

#endif //