#ifndef __CONCRETE_SUBJECT__HPP__
#define __CONCRETE_SUBJECT__HPP__

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <memory>
#include "../subject/subject.hpp"

typedef enum Concrete_Subject_SOA_Type
{
    SOA_TYPE_1,
    SOA_TYPE_2,
    SOA_TYPE_MAX,
};

class ConcreteSubject_0 : public Subject
{
    public:
    ConcreteSubject_0(std::string name):m_name(name)
    {
        std::cout << "ConcreteSubject constructor " << name << std::endl;
    };
    ~ConcreteSubject_0()
    {
        std::cout << "ConcreteSubject destructor " << m_name << std::endl;;
    };

    ConcreteSubject_0& operator=(const ConcreteSubject_0&) = delete;
    ConcreteSubject_0(const ConcreteSubject_0&) = delete;

    static ConcreteSubject_0& get_instance()
    {
        static ConcreteSubject_0 instance;
        return instance;
    }

    void RegisterSuject(uint16_t DID, std::shared_ptr<observer> pobserver);

    void UnregisterSuject(uint16_t DID,std::shared_ptr<observer> pobserver);

    void Notify(uint16_t DID , void* data,unsigned int len);

    private:
    ConcreteSubject_0()
    {
        std::cout << "ConcreteSubject_0 default Constructor" << std::endl;
    }
    std::map<uint16_t,std::vector<std::shared_ptr<observer>>> Soamap;
    std::list<std::shared_ptr<observer>> m_observerslist;
    std::string m_name;
};

#endif