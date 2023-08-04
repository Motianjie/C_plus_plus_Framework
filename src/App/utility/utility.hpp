/*
 * @FilePath: /C_plus_plus_Framework/src/App/utility/utility.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-04 15:52:52
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __UTILITY__
#define __UTILITY__

#include "Platform_Types.hpp"
#include <vector>
#include <algorithm>

/**
 * @description: 从vector乱序列中匹配协议头
 * @return {std::vector<uint8>::iterator 迭代器表征协议头的位置}
 */
extern std::vector<uint8>::iterator findProtocolHeader(std::vector<uint8>& data, std::vector<uint8>& header);




#endif