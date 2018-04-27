cmake_minimum_required(VERSION 3.5)
project(Reversi)

set(CMAKE_CXX_STANDARD 14)

add_executable(Reversi main.cpp Reversi.cpp Reversi.h MCTSNode.cpp MCTSNode.h)