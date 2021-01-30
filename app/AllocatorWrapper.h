#ifndef _ALLOCATOR_WRAPPER_H_
#define _ALLOCATOR_WRAPPER_H_

#include "SimpleStaticAllocator.h"

namespace OS {

    class AllocatorWrapper {
    private:
        static constexpr size_t CHUNK_SIZE = 2;
        static constexpr size_t POOL_SIZE = 10;

        using ChunkType = uint8_t;
        using ChunkTypePointer = ChunkType *;

    private:
        static AllocatorLib::SimpleStaticAllocator<ChunkType, CHUNK_SIZE, POOL_SIZE> allocator;

    private:
        static void lockAllocatorMutex();

        static void releaseAllocatorMutex();

    public:
        static ChunkTypePointer allocate();

        static void free(ChunkTypePointer chunk);
    };

}

#endif
