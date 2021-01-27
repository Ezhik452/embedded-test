#include <iostream>

#include "lib/include/SimpleStaticAllocator.h"

int main()
{
    TestTask::SimpleStaticAllocator<uint32_t, 1, 10> allocator;
    allocator.init();

    auto e0 = allocator.allocate();
    std::cout << e0 << std::endl;

    auto e1 = allocator.allocate();
    std::cout << e1 << std::endl;

    allocator.free(e0);
}
