set(target "app")

add_executable(${target} main.cpp AllocatorWrapper.cpp AllocatorWrapper.h)

target_link_libraries(${target} PRIVATE simpleStaticAllocator)