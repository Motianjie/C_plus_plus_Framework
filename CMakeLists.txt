#cmake version require
cmake_minimum_required(VERSION 3.0)

#User settings
#Project name
set(PROJNAME AG_OBSERVER_MODE)
#App path
set(APP_DIR ${CMAKE_SOURCE_DIR}/src/App/)
#Middleware path
set(MIDDLEWARE_DIR ${CMAKE_SOURCE_DIR}/src/Middleware/)
#Testcase path
set(TEST_DIR ${CMAKE_SOURCE_DIR}/src/Testcase/)


#project name
project(${PROJNAME})  

#compile option
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-elide-constructors -g -pthread -Wall")

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

#include
include_directories(${APP_DIR}Concrete_observer_sample0)
include_directories(${APP_DIR}Concrete_observer_sample1)
include_directories(${APP_DIR}Concrete_subject)
include_directories(${APP_DIR}observer)
include_directories(${APP_DIR}subject)
include_directories(${APP_DIR}EpollTcp)
include_directories(${APP_DIR}EpollTcp/message)
include_directories(${APP_DIR}EpollTcp/routing)
include_directories(${APP_DIR}utility)
include_directories(${APP_DIR})
include_directories(${MIDDLEWARE_DIR}spdlog)
include_directories(${MIDDLEWARE_DIR}nlohmann)
include_directories(${MIDDLEWARE_DIR}os)
include_directories(${MIDDLEWARE_DIR})
include_directories(${TEST_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/)


#static library
add_subdirectory(${APP_DIR}Concrete_observer_sample0)
add_subdirectory(${APP_DIR}Concrete_observer_sample1)
add_subdirectory(${APP_DIR}Concrete_subject)
add_subdirectory(${APP_DIR}EpollTcp/routing)
add_subdirectory(${APP_DIR}EpollTcp/message)
add_subdirectory(${APP_DIR}EpollTcp)
add_subdirectory(${APP_DIR}utility)
add_subdirectory(${TEST_DIR})

#exe file
add_executable(${PROJECT_NAME} main.cpp)
#

#link library

target_link_libraries(${PROJECT_NAME} Testcase)
target_link_libraries(${PROJECT_NAME} Concrete_observer_sample0)
target_link_libraries(${PROJECT_NAME} Concrete_observer_sample1)
target_link_libraries(${PROJECT_NAME} Concrete_subject)
target_link_libraries(${PROJECT_NAME} EpollTcp)
target_link_libraries(${PROJECT_NAME} routing)
target_link_libraries(${PROJECT_NAME} message)
target_link_libraries(${PROJECT_NAME} utility)


