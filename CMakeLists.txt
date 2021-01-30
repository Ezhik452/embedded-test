cmake_minimum_required(VERSION 3.14.0)
project(SimpleStaticAllocator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(externals/catch2)

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(app)