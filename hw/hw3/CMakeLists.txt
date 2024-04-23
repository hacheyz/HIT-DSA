cmake_minimum_required(VERSION 3.0)
project(hw3)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw3
        main.cpp
        graph.h
        graph_matrix.cpp
        graph_list.cpp
        support/stack.h
        support/queue.h
        forest.h test.h)
