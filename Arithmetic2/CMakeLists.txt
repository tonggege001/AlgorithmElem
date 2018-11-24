cmake_minimum_required(VERSION 3.8)
project(Arithmetic2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BestBinaryTree.cpp FloydWashall.cpp)
add_executable(Arithmetic2 ${SOURCE_FILES})