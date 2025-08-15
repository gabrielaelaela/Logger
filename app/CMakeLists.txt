cmake_minimum_required(VERSION 3.21)
project(LoggerLib)

option(BUILD_SHARED_LIBS "Build as a shared library" ON)

add_library(loglib STATIC src/FileLogger.cpp)
target_include_directories(loglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)