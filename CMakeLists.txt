cmake_minimum_required(VERSION 3.13)  # CMake version check
project(
    yayadb-modules
    VERSION 
    LANGUAGES C
)               # Create project "simple_example"


# protocol
add_library(socket STATIC protocol/src/socke.c)
add_library(proto STATIC protocol/src/protocol.c)


