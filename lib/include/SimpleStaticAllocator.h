#ifndef _SIMPLE_STATIC_ALLOCATOR_H_
#define _SIMPLE_STATIC_ALLOCATOR_H_

#include <cstdint>

#include "SimpleStack.h"

namespace AllocatorLib {
    using MutexLockFuntionType = void (*)();
    using MutexReleaseFuntionType = void (*)();

    template<typename Te, size_t chunkSize, size_t poolSize>
    class SimpleStaticAllocator {
        using ChunkType = Te;
        using ChunkTypePointer = ChunkType *;

    private:
        static constexpr uint32_t POOL_ELEMENTS_COUNT = poolSize / chunkSize;

        static_assert(POOL_ELEMENTS_COUNT > 0, "Pool size must be greater than 0");

    private:
        ChunkType pool[POOL_ELEMENTS_COUNT];
        SimpleStack<ChunkTypePointer, POOL_ELEMENTS_COUNT> freeStack;

        MutexLockFuntionType lock = nullptr;
        MutexReleaseFuntionType release = nullptr;

    public:
        SimpleStaticAllocator(MutexLockFuntionType lockFunction, MutexReleaseFuntionType releaseFunction) {

            lock = lockFunction;
            release = releaseFunction;

            freeStack.init();

            for (auto &element : pool) {
                freeStack.push(&element);
            }
        }

        constexpr size_t size() noexcept {
            return POOL_ELEMENTS_COUNT;
        }

        size_t count() const noexcept {
            if (lock != nullptr) {
                lock();
            }

            size_t res = POOL_ELEMENTS_COUNT - freeStack.count();

            if (release != nullptr) {
                release();
            }

            return res;
        }


        ChunkTypePointer allocate() {
            if (lock != nullptr) {
                lock();
            }

            ChunkTypePointer res = nullptr;

            if (!freeStack.isEmpty()) {
                res = freeStack.pop();
            }

            if (release != nullptr) {
                release();
            }

            return res;
        }

        void free(ChunkTypePointer &chunk) {
            if (lock != nullptr) {
                lock();
            }

            if (!freeStack.isFull() && chunk != nullptr) {
                freeStack.push(chunk);
                chunk = nullptr;
            }

            if (release != nullptr) {
                release();
            }
        }
    };
}

#endif
