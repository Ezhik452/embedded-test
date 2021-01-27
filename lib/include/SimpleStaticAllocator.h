#ifndef _SIMPLE_STATIC_ALLOCATOR_H_
#define _SIMPLE_STATIC_ALLOCATOR_H_

#include <cstdint>

#include "SimpleStack.h"

namespace TestTask {
    template<typename ElementType, uint32_t blockSize, uint32_t poolSize>
    class SimpleStaticAllocator {
        using ElementTypePointer = ElementType *;

    private:
        static constexpr uint32_t POOL_ELEMENTS_COUNT = poolSize / blockSize;

    private:
        ElementType pool[POOL_ELEMENTS_COUNT];
        SimpleStack<ElementTypePointer, POOL_ELEMENTS_COUNT> freeStack;

    public:
        void init() {
            freeStack.init();

            for (uint32_t i = 0; i < POOL_ELEMENTS_COUNT; i++) {
                freeStack.push(&pool[i]);
            }
        }

        ElementTypePointer allocate() {
            if (!freeStack.isEmpty()) {
                return freeStack.pop();
            }

            return nullptr;
        }

        void free(ElementTypePointer element) {
            if (!freeStack.isFull()) {
                freeStack.push(element);
            }
        }
    };
}

#endif
