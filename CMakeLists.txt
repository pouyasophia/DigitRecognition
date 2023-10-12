cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(DigRecognition)

include_directories(inc)

file(GLOB project_SRCS "src/*.cpp")

add_executable(digRecog ${project_SRCS})
