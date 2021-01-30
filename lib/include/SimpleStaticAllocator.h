#ifndef _SIMPLE_STATIC_ALLOCATOR_H_
#define _SIMPLE_STATIC_ALLOCATOR_H_

#include <cstdint>

#include "SimpleStack.h"

namespace AllocatorLib {
    using MutexLockFuntionType = void (*)();
    using MutexReleaseFuntionType = void (*)();

    template<typename Te, size_t chunkSize, size_t poolSize>
    class SimpleStaticAllocator {
        using ElementType = Te;
        using ElementTypePointer = ElementType *;

    private:
        static constexpr uint32_t POOL_ELEMENTS_COUNT = poolSize / chunkSize;

    private:
        ElementType pool[POOL_ELEMENTS_COUNT];
        SimpleStack<ElementTypePointer, POOL_ELEMENTS_COUNT> freeStack;

        MutexLockFuntionType lock = nullptr;
        MutexReleaseFuntionType release = nullptr;

    public:
        SimpleStaticAllocator(MutexLockFuntionType lockFunction, MutexReleaseFuntionType releaseFunction) {

            lock = lockFunction;
            release = releaseFunction;

            freeStack.init();

            for (uint32_t i = 0; i < POOL_ELEMENTS_COUNT; i++) {
                freeStack.push(&pool[i]);
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


        ElementTypePointer allocate() {
            if (lock != nullptr) {
                lock();
            }

            ElementTypePointer res = nullptr;

            if (!freeStack.isEmpty()) {
                res = freeStack.pop();
            }

            if (release != nullptr) {
                release();
            }

            return res;
        }

        void free(ElementTypePointer &element) {
            if (lock != nullptr) {
                lock();
            }

            if (!freeStack.isFull() && element != nullptr) {
                freeStack.push(element);
                element = nullptr;
            }

            if (release != nullptr) {
                release();
            }
        }
    };
}

#endif
