#ifndef __CONCRETE_OBSERVERD__HPP__
#define __CONCRETE_OBSERVERD__HPP__

#include <iostream>
#include <string>
#include "observer.hpp"
#include "spdlog/spdlog.h"
class ConcreteObserver_sample_0 : public Observer
{
public:
    ~ConcreteObserver_sample_0();
    static std::shared_ptr<ConcreteObserver_sample_0> get_instance()
    {
        static std::shared_ptr<ConcreteObserver_sample_0> instance(new ConcreteObserver_sample_0());
        return instance;
    }
    void Notify(uint16_t DID, void* data,unsigned int len);

private:
    ConcreteObserver_sample_0()
    {
        m_name="ConcreteObserver_sample_0";
        spdlog::info("[{}] default Constructor",this->m_name);
    }
    ConcreteObserver_sample_0& operator=(const ConcreteObserver_sample_0&) = delete;
    ConcreteObserver_sample_0(const ConcreteObserver_sample_0&) = delete;
private:
    std::string m_name;
};

#endif //