cmake_minimum_required(VERSION 3.0)
aux_source_directory(. LIB_SRCS)
add_library(Concrete_observer STATIC ${LIB_SRCS})

