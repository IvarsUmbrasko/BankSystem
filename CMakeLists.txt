cmake_minimum_required(VERSION 4.0)
project(BankSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(BankSystem main.cpp
        Account.cpp
        Account.h)
