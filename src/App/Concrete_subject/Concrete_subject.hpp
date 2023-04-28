#ifndef __CONCRETE_SUBJECT__HPP__
#define __CONCRETE_SUBJECT__HPP__

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <memory>
#include "subject.hpp"
#include "spdlog/spdlog.h"


class ConcreteSubject_0 : public Subject
{
    public:
    static ConcreteSubject_0* get_instance()
    {
        static ConcreteSubject_0* instance;
        return instance;
    }

    void RegisterSuject(uint16_t DID, observer* pobserver);

    void UnregisterSuject(uint16_t DID,observer* pobserver);

    void Notify(uint16_t DID , void* data,unsigned int len);

    enum Concrete_Subject_SOA_Type : uint16_t
    {
        SOA_TYPE_1,
        SOA_TYPE_2,
        SOA_TYPE_MAX,
    };
    private:
    ConcreteSubject_0()
    {
        spdlog::info("ConcreteObserver Constructor");
    }
    ~ConcreteSubject_0()
    {
        spdlog::info("ConcreteSubject destructor");
    };
    ConcreteSubject_0& operator=(const ConcreteSubject_0&) = delete;
    ConcreteSubject_0(const ConcreteSubject_0&) = delete;

    std::map<uint16_t,std::vector<observer*>> Soamap;
    std::string m_name;
};

#endif