cmake_minimum_required(VERSION 3.5)
project(Reversi)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(Reversi main.cpp Reversi.cpp Reversi.h MCTSNode.cpp MCTSNode.h)
target_link_libraries(Reversi ${Boost_LIBRARIES})