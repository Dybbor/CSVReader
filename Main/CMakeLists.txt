cmake_minimum_required(VERSION 3.5)
project(csvreader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set (SRC Source.cpp ReaderCSV.h ReaderCSV.cpp)


add_executable(csvreader ${SRC} ${HEADERS})