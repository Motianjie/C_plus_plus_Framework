#include <iostream>
#include <memory>
#include "Concrete_subject.hpp"
#include "Concreteobserverd.hpp"
#include "spdlog/spdlog.h"

// #define UNREGISTER_TEST

void spdlog_test()
{
    spdlog::set_level(spdlog::level::info); // Set global log level to debug
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");
}

int main(int argc, char **argv)
{
    // spdlog_test();
    ConcreteObserver_0* pobserver_0 = ConcreteObserver_0::get_instance();
    ConcreteObserver_0* pobserver_1 = ConcreteObserver_0::get_instance();

    ConcreteSubject_0* subject = ConcreteSubject_0::get_instance();

    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_1, pobserver_0);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_1, pobserver_1);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_2, pobserver_0);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_2, pobserver_1);

#ifdef UNREGISTER_TEST
    subject.UnregisterSuject(ConcreteSubject_0::SOA_TYPE_1,pobserver_0);
    subject.UnregisterSuject(ConcreteSubject_0::SOA_TYPE_1,pobserver_1);
    subject.UnregisterSuject(ConcreteSubject_0::SOA_TYPE_2,pobserver_0);
    subject.UnregisterSuject(ConcreteSubject_0::SOA_TYPE_2,pobserver_1);
#endif
    uint8_t datatest[5] = {0x00,0x01,0x02,0x03,0x04};
    subject->Notify(ConcreteSubject_0::SOA_TYPE_1, datatest, sizeof(datatest));
    subject->Notify(ConcreteSubject_0::SOA_TYPE_2, datatest, sizeof(datatest));
    return 0;
}
