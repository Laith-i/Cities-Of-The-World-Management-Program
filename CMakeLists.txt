cmake_minimum_required(VERSION 3.29)
project(5004_CW)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(5004_CW src/main.cpp
        include/City.h
        src/City.cpp
        include/citymanager.h
        src/citymanager.cpp
        include/inputHandler.h
        src/inputhandler.cpp
        include/Utilities.h
        src/Utilities.cpp)
