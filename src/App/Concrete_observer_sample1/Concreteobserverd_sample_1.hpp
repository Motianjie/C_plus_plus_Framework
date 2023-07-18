#ifndef __CONCRETE_OBSERVERD__SAMPLE1__HPP__
#define __CONCRETE_OBSERVERD__SAMPLE1__HPP__

#include <iostream>
#include <string>
#include "observer.hpp"
#include "spdlog/spdlog.h"
class ConcreteObserver_sample_1 : public Observer
{
public:
    ~ConcreteObserver_sample_1();
    static std::shared_ptr<ConcreteObserver_sample_1> get_instance()
    {
        static std::shared_ptr<ConcreteObserver_sample_1> instance(new ConcreteObserver_sample_1());
        return instance;
    }
    void Notify(uint16_t DID, void* data,unsigned int len);

private:
    ConcreteObserver_sample_1()
    {
        m_name="ConcreteObserver_sample_1";
        spdlog::info("[{}] default Constructor",this->m_name);
    }
    ConcreteObserver_sample_1& operator=(const ConcreteObserver_sample_1&) = delete;
    ConcreteObserver_sample_1(const ConcreteObserver_sample_1&) = delete;
private:
    std::string m_name;
};

#endif //