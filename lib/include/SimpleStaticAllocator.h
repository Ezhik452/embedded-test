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

    public:
        SimpleStaticAllocator(MutexLockFuntionType lockFunction, MutexReleaseFuntionType releaseFunction) {
            freeStack.init();

            for (uint32_t i = 0; i < POOL_ELEMENTS_COUNT; i++) {
                freeStack.push(&pool[i]);
            }
        }

        constexpr size_t size() noexcept {
            return POOL_ELEMENTS_COUNT;
        }

        size_t count() const noexcept {
            return POOL_ELEMENTS_COUNT - freeStack.count();
        }


        ElementTypePointer allocate() {
            if (!freeStack.isEmpty()) {
                return freeStack.pop();
            }

            return nullptr;
        }

        void free(ElementTypePointer &element) {
            if (!freeStack.isFull() && element != nullptr) {
                freeStack.push(element);
                element = nullptr;
            }
        }
    };
}

#endif
