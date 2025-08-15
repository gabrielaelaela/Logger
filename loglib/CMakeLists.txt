cmake_minimum_required(VERSION 3.21)
project(LoggerLib LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build as a shared library" ON)

add_library(${PROJECT_NAME} STATIC src/FileLogger.cpp src/AbstractLogger.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
