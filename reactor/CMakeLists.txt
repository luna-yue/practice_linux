cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



add_executable(reactor_server Main.cpp)
target_link_libraries(reactor_server jsoncpp)
