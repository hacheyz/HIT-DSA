cmake_minimum_required(VERSION 3.0)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2 main.cpp preprocessing.h preprocessing.cpp huffman_tree.h huffman_tree.cpp store.h encode.h encode.cpp stack.h decode.cpp decode.h evaluate.cpp evaluate.h)
