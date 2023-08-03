#include "routing_manager.hpp"

routing_manager::routing_manager() : routing_manager_thread_m(std::bind(&routing_manager::routing_manager_thread,this))
{
    uint32 it_max = 5;
    for(int i = 0;i < it_max;++i)
    {
        serializers_.push(std::make_shared<serializer>());
        deserializers_.push(std::make_shared<deserializer>());
    }
}

routing_manager::~routing_manager()
{
    routing_manager_thread_m.join();
}

std::shared_ptr<serializer> routing_manager::get_serializer()
{
    std::unique_lock<std::mutex> its_lock(serializer_mutex_);
    while (serializers_.empty())
    {
        std::cout << " has no available serializer. Waiting..." << std::endl;
        serializer_condition_.wait(its_lock);
        std::cout << " now checking for available serializer." << std::endl;
    } 

    auto it_serializer = serializers_.front();
    serializers_.pop();
    return it_serializer;
}

void routing_manager::put_serializer(const std::shared_ptr<serializer> &_serializer)
{
    std::lock_guard<std::mutex> its_lock(serializer_mutex_);
    serializers_.push(_serializer);
    serializer_condition_.notify_one();
}

std::shared_ptr<deserializer> routing_manager::get_deserializer()
{
    std::unique_lock<std::mutex> its_lock(deserializer_mutex_);
    while (deserializers_.empty())
    {
        std::cout << " has no available deserializer. Waiting..." << std::endl;
        deserializer_condition_.wait(its_lock);
        std::cout << " now checking for deavailable serializer." << std::endl;
    } 

    auto it_deserializer = deserializers_.front();
    deserializers_.pop();
    return it_deserializer;
}

void routing_manager::put_deserializer(const std::shared_ptr<deserializer> &_deserializer)
{
    std::lock_guard<std::mutex> its_lock(deserializer_mutex_);
    deserializers_.push(_deserializer);
    deserializer_condition_.notify_one();
}

boolean routing_manager::push_raw_data(const uint8 *data, const uint32 len)
{
    if(data == nullptr || len == 0)
        return false;

    try
    {
        data_raw_in.insert(data_raw_in.end(),data,data+len);
    }catch(const std::bad_alloc& e)
    {
        std::cout << "bad alloc" << e.what() << std::endl;
        return false;
    }
    return true;
}

void routing_manager::routing_manager_thread()
{
    std::cout << "routing_manager_thread created" << std::endl;
    std::string threadName = "routing_manager_thread";
    pthread_setname_np(pthread_self(), threadName.c_str());
    while(1)
    {
        std::cout << "routing_manager_thread is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}