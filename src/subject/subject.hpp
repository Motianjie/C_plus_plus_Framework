#ifndef __SUBJECT__HPP__
#define __SUBJECT__HPP__
#include <iostream>
#include "../observer/observer.hpp"

/// @brief Interface of Subject of Observer mode
class Subject
{
public:
    /// @brief Constructor
    Subject(void)
    {
        std::cout << "Subject constructor" << std::endl;
    };

    /// @brief Destructor
    virtual ~Subject()
    {
        std::cout << "Subject destructor" << std::endl;
    };

    /// @brief Interface of Register subject
    /// @param ptr of Concrete Observer 
    virtual void RegisterSuject(uint16_t DID,std::shared_ptr<observer> pobserver) = 0;

    /// @brief Interface of Unregister subject
    /// @param ptr of Concrete Observer
    virtual void UnregisterSuject(uint16_t DID,std::shared_ptr<observer> pobserver) = 0;

    /// @brief Suject notify observers
    /// @param date The data suject wants to notify observers
    /// @param len The len of data suject wants to notify observers
    virtual void Notify(uint16_t DID ,void* data,unsigned int len) = 0;
};

#endif //