#ifndef __SUBJECT__HPP__
#define __SUBJECT__HPP__
#include <iostream>
#include "observer.hpp"
#include "spdlog/spdlog.h"
/// @brief Interface of Subject of Observer mode
class Subject
{
public:
    /// @brief Constructor
    Subject()
    {
        spdlog::info("[Subject] constructor");
    };

    /// @brief Destructor
    virtual ~Subject()
    {
        spdlog::info("[Subject] destructor");
    };

    /// @brief Interface of Register subject
    /// @param ptr of Concrete Observer 
    virtual void RegisterSuject(uint16_t DID,const std::shared_ptr<Observer>& pobserver) = 0;

    /// @brief Interface of Unregister subject
    /// @param ptr of Concrete Observer
    virtual void UnregisterSuject(uint16_t DID,const std::shared_ptr<Observer>& pobserver) = 0;

    /// @brief Suject notify observers
    /// @param date The data suject wants to notify observers
    /// @param len The len of data suject wants to notify observers
    virtual void Notify(uint16_t DID ,void* data,unsigned int len) = 0;
};

#endif //