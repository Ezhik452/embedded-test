cmake_minimum_required(VERSION 3.14.0)
project(SimpleStaticAllocator)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestApp main.cpp)
target_link_libraries(TestApp SimpleStaticAllocator)

add_subdirectory(lib)