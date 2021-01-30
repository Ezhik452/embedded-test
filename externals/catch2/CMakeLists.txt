set(target "catch2")

add_library(${target} src/catch_amalgamated.cpp)

target_include_directories(${target} PUBLIC include)
