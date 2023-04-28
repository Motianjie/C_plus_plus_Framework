#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#include <iostream>
#include <memory>
#include "Concrete_subject.hpp"
#include "Concreteobserverd.hpp"
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
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

void json_test()
{
    nlohmann::json j;

    // add a number that is stored as double (note the implicit conversion of j to an object)
    j["pi"] = 3.141;
    // add a Boolean that is stored as bool
    j["happy"] = true;
    // add a string that is stored as std::string
    j["name"] = "Niels";
    // add another null object by passing nullptr
    j["nothing"] = nullptr;
    // add an object inside the object
    j["answer"]["everything"] = 42;
    // add an array that is stored as std::vector (using an initializer list)
    j["list"] = { 1, 0, 2 };
    // add another object (using an initializer list of pairs)
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };

    std::cout << j << std::endl;
    std::string json_string = j.dump(4);
    std::cout << json_string << std::endl;

    nlohmann::json j_parse = nlohmann::json::parse(json_string);
    if(j_parse.contains("pi"))
    {
        float pi = j_parse["pi"];
        std::cout << pi << std::endl;
    }

}

void log_test()
{
    auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "/home/thor/Desktop/Reconsitution_C++/log/async_log.txt");  
    SPDLOG_LOGGER_INFO(async_file,"test");
}


int main(int argc, char **argv)
{
    // json_test();
    // spdlog_test();
    log_test();
    ConcreteObserver_0* pobserver_0 = ConcreteObserver_0::get_instance();
    ConcreteObserver_0* pobserver_1 = ConcreteObserver_0::get_instance();

    ConcreteSubject_0* subject = ConcreteSubject_0::get_instance();

    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_1, pobserver_0);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_1, pobserver_1);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_2, pobserver_0);
    subject->RegisterSuject(ConcreteSubject_0::SOA_TYPE_2, pobserver_1);

#ifdef UNREGISTER_TEST
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_1,pobserver_0);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_1,pobserver_1);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_2,pobserver_0);
    subject->UnregisterSuject(ConcreteSubject_0::SOA_TYPE_2,pobserver_1);
#endif
    uint8_t datatest[5] = {0x00,0x01,0x02,0x03,0x04};
    subject->Notify(ConcreteSubject_0::SOA_TYPE_1, datatest, sizeof(datatest));
    subject->Notify(ConcreteSubject_0::SOA_TYPE_2, datatest, sizeof(datatest));
    return 0;
}
