#ifndef __OBSERVER__HPP__
#define __OBSERVER__HPP__

#include <iostream>
#include <spdlog/spdlog.h>

/// @brief Interface of Observer of Observer mode
class observer
{
public:
    /// @brief Constructor
    observer(void) 
    {
        spdlog::info("observer constructor");
    };

    /// @brief Destructor
    virtual ~observer()
    {
        spdlog::info("observer destrcutor");
    };

    /// @brief Suject notify observers
    /// @param date The data suject wants to notify observers
    /// @param len The len of data suject wants to notify observers
    virtual void Notify(uint16_t DID ,void* data,unsigned int len) = 0;

    /// @brief Get Name of Concrete object
    /// @return name of the object
    virtual std::string GetName(void) = 0;
};


#endif //