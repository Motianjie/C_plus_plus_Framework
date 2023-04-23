#cmake version require
cmake_minimum_required(VERSION 3.0)

#User settings
#Project name
set(PROJNAME AG_OBSERVER_MODE)
#App path
set(APP_DIR ${CMAKE_SOURCE_DIR}/src/App/)
#Middleware path
set(MIDDLEWARE_DIR ${CMAKE_SOURCE_DIR}/src/Middleware/)

#project name
project(${PROJNAME})  

#compile option
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-elide-constructors -g -pthread -Wall")

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

#include
include_directories(${APP_DIR}Concrete_observer)
include_directories(${APP_DIR}Concrete_subject)
include_directories(${APP_DIR}observer)
include_directories(${APP_DIR}subject)
include_directories(${APP_DIR})
include_directories(${MIDDLEWARE_DIR}Middleware/spdlog)
include_directories(${MIDDLEWARE_DIR}Middleware)
include_directories(${MIDDLEWARE_DIR})

#static library
add_subdirectory(${APP_DIR}Concrete_observer)
add_subdirectory(${APP_DIR}Concrete_subject)

#exe file
add_executable(${PROJECT_NAME} main.cpp)
#

#link library
target_link_libraries(${PROJECT_NAME} Concrete_observer)
target_link_libraries(${PROJECT_NAME} Concrete_subject)

