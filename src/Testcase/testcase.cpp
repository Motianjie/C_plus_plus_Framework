#include "Platform_Types.hpp"
#include "testcase.hpp"
#include <iostream>
#include <functional>
#include <map>

struct sockettest
{
    sint32 id;
    uint8 test;
    uint16 test_len;
    bool operator<(const sockettest& other) const 
    {
        return id < other.id;
    }
};

static void test_cb(sint32 did,void* data,uint32 len)
{
    std::cout << "test_cb"<<std::endl;
}

static std::function<void(sint32,void*,uint32)> func = std::bind(&test_cb,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);

void test_()//测试std::map的键可以是自定义的结构体，但是要重写<,值也可以是函数指针
{
    sint32 did =2;
    uint8 buffer[10] = {1};
    uint32 len =sizeof(buffer);
    // std::map<struct sockettest,void(*)(sint32,void*,uint32)> maptest;
    std::map<struct sockettest,std::function<void(sint32,void*,uint32)>> maptest;
    sockettest test1;
    test1.test = 1;
    test1.test_len = 10;

    sockettest test2;
    test2.test = 2;
    test2.test_len = 20;

    maptest.insert(std::make_pair(test1,func));
    maptest.insert(std::make_pair(test2,func));

    for(auto maps : maptest)
    {
        maps.second(did,buffer,len);
    }
}