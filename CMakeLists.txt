cmake_minimum_required(VERSION 3.0)

project(OBSERVER_MODE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-elide-constructors -g -pthread -Wall")

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
#include
include_directories(${CMAKE_SOURCE_DIR}/src/Concrete_observer)
include_directories(${CMAKE_SOURCE_DIR}/src/Concrete_subject)
include_directories(${CMAKE_SOURCE_DIR}/src/observer)
include_directories(${CMAKE_SOURCE_DIR}/src/subject)

#static library
add_subdirectory(${CMAKE_SOURCE_DIR}/src/Concrete_observer)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/Concrete_subject)

#exe file
add_executable(observer_mode main.cpp)
#

#link library
target_link_libraries(observer_mode Concrete_observer)
target_link_libraries(observer_mode Concrete_subject)



