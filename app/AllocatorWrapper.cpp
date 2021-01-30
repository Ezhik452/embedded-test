#include "AllocatorWrapper.h"

namespace OS {
    AllocatorLib::SimpleStaticAllocator<
            AllocatorWrapper::ChunkType,
            AllocatorWrapper::CHUNK_SIZE,
            AllocatorWrapper::POOL_SIZE> AllocatorWrapper::allocator(lockAllocatorMutex, releaseAllocatorMutex);

    void AllocatorWrapper::lockAllocatorMutex() {
        //TODO: add mutex lock
    }

    void AllocatorWrapper::releaseAllocatorMutex() {
        //TODO: add mutex release
    }

    AllocatorWrapper::ChunkTypePointer AllocatorWrapper::allocate() {
        return allocator.allocate();
    }

    void AllocatorWrapper::free(ChunkTypePointer chunk) {
        allocator.free(chunk);
    }
}