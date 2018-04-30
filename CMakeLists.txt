cmake_minimum_required(VERSION 3.5)
project(Reversi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -pthread -lboost_system ${CMAKE_CXX_FLAGS}")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(Reversi main.cpp Reversi.cpp Reversi.h MCTSNode.cpp MCTSNode.h server.cpp server.hpp)
target_link_libraries(Reversi ${Boost_LIBRARIES})
