cmake_minimum_required(VERSION 3.0)

project(OBSERVER_MODE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-elide-constructors -g -pthread -Wall")
set(APP_DIR ${CMAKE_SOURCE_DIR}/src/App/)
set(MIDDLEWARE_DIR ${CMAKE_SOURCE_DIR}/src/Middleware/)
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
add_executable(observer_mode main.cpp)
#

#link library
target_link_libraries(observer_mode Concrete_observer)
target_link_libraries(observer_mode Concrete_subject)

