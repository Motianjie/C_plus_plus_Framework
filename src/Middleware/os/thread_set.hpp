/*
 * @FilePath: /C_plus_plus_Framework/src/Middleware/os/thread_set.hpp
 * @Description:  
 * @Author: Motianjie 13571951237@163.com
 * @Version: 0.0.1
 * @LastEditors: Motianjie 13571951237@163.com
 * @LastEditTime: 2023-08-18 18:14:28
 * Copyright    : ASENSING CO.,LTD Copyright (c) 2023.
 */
#ifndef __thread_set__
#define __thread_set__

#include "Platform_Types.hpp"
#include "spdlog/spdlog.h"
#include "sys/syscall.h"
#include <iostream>
#include <unordered_map>
#include <sched.h>
#include <thread>
#include <bitset>
#include <sys/sysinfo.h>
#include <string>
#include <cstring>
#include <cerrno>

#define  cpu_id_t uint8
class thread_set
{
public:
    thread_set(const std::string& _thread_name,std::thread& _thread,uint8 _cpu_id):thread_name_m(_thread_name),
                                                                                thread_m(_thread),
                                                                                cpu_id_m(_cpu_id)
    {
        cpu_bind();
    }
    ~thread_set()
    {

    }

    void cpu_bind()
    { 
        pthread_t threadId = pthread_self();
        sint32 cpunums = sysconf(_SC_NPROCESSORS_ONLN);
        cpu_set_t cpuset;
        pid_t tid;
        tid=syscall(SYS_gettid);
        CPU_ZERO(&cpuset);
        CPU_SET(cpu_id_m, &cpuset);
        int result = pthread_setaffinity_np(threadId, sizeof(cpu_set_t), &cpuset);
        if (result < 0) 
        {
            spdlog::error("Failed to bind thread to CPU core!");
        }
        
        result = pthread_getaffinity_np(threadId,sizeof(cpu_set_t), &cpuset);
        if (result < 0) 
        {
            spdlog::error("Failed to get bind thread to CPU core!");
        }

        for(int i = 0; i < cpunums;i++)
        {
            if (CPU_ISSET(i, &cpuset))
            {
                if(i == cpu_id_m)
                {
                    result = pthread_setname_np(threadId, thread_name_m.c_str());
                    if(result < 0)
                    {
                        spdlog::error("set threadname failed[{}]",std::strerror(errno));
                    }
                    spdlog::info("thread[{}] pid[{:d}] bind cpu[{:d}] success",thread_name_m.c_str(),tid,cpu_id_m);
                }else
                {
                    spdlog::error("thread[{}] bind cpu[{:d}] failed",thread_name_m.c_str(),cpu_id_m);
                }   
            }
        }

    }

private:
    std::string thread_name_m;
    std::thread& thread_m;
    cpu_id_t cpu_id_m;
};





#endif