set(target "tests")

add_executable(${target} SimpleAllocatorTests.cpp)

target_link_libraries(${target} PRIVATE catch2 simpleStaticAllocator)