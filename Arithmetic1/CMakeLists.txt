cmake_minimum_required(VERSION 3.8)
project(Arithmetic1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BigInteger.cpp BigInteger.h MinLen.cpp test.cpp)
add_executable(Arithmetic1 ${SOURCE_FILES} BigInteger.cpp BigInteger.h)