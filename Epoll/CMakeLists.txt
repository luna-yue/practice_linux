cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(EpollServer EpollServer.cpp)

add_executable(Client Client.cpp)