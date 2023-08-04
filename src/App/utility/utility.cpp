/*
 * @FilePath: /C_plus_plus_Framework/src/App/utility/utility.cpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-04 11:10:03
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#include "utility.hpp"

std::vector<uint8>::iterator findProtocolHeader(std::vector<uint8>& data, std::vector<uint8>& header)
{
    auto headerPos = std::search(data.begin(), data.end(), header.begin(), header.end());
    return headerPos;
}

