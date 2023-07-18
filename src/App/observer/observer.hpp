#ifndef __OBSERVER__HPP__
#define __OBSERVER__HPP__

#include <iostream>
#include <spdlog/spdlog.h>

/// @brief Interface of Observer of Observer mode
class Observer
{
public:
    /// @brief Constructor
    Observer(void) 
    {
        spdlog::info("[observer] constructor");
    };

    /// @brief Destructor
    virtual ~Observer()
    {
        spdlog::info("[observer] destrcutor");
    };

    /// @brief Suject notify observers
    /// @param date The data suject wants to notify observers
    /// @param len The len of data suject wants to notify observers
    virtual void Notify(uint16_t DID ,void* data,unsigned int len) = 0;

};


#endif //