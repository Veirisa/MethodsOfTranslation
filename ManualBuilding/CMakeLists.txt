cmake_minimum_required(VERSION 3.9)
project(Task2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Task2 tester.cpp parser_exception.h lexical_analyzer.cpp lexical_analyzer.h parser.cpp parser.h)