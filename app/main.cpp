#include "AllocatorWrapper.h"

int main()
{
    auto chunk = OS::AllocatorWrapper::allocate();
    OS::AllocatorWrapper::free(chunk);
}
