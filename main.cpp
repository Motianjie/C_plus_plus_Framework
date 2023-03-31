#include <iostream>
#include <memory>
#include "./src/Concrete_subject/Concrete_subject.hpp"
#include "./src/Concrete_observer/Concreteobserverd.hpp"


int main(int argc, char **argv)
{
    std::shared_ptr<observer> pobserver_0(new ConcreteObserver_0("Observer_0"));
    std::shared_ptr<observer> pobserver_1(new ConcreteObserver_0("Observer_1"));

    Subject& subject = ConcreteSubject_0::get_instance();

    subject.RegisterSuject(SOA_TYPE_1,pobserver_0);
    subject.RegisterSuject(SOA_TYPE_1,pobserver_1);
    subject.RegisterSuject(SOA_TYPE_2,pobserver_0);
    subject.RegisterSuject(SOA_TYPE_2,pobserver_1);

    // subject.UnregisterSuject(SOA_TYPE_1,pobserver_0);
    // subject.UnregisterSuject(SOA_TYPE_1,pobserver_1);
    // subject.UnregisterSuject(SOA_TYPE_2,pobserver_0);
    // subject.UnregisterSuject(SOA_TYPE_2,pobserver_1);


    uint8_t datatest[5] = {0x00};
    subject.Notify(SOA_TYPE_1,datatest,sizeof(datatest));
    subject.Notify(SOA_TYPE_2,datatest,sizeof(datatest));

    return 0;
}
