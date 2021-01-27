#ifndef _SIMPLE_STACK_H_
#define _SIMPLE_STACK_H_

#include <array>
#include <cstdint>
#include <iostream>

template<typename ElementType, uint32_t size>
class SimpleStack {
    static_assert(size > 0, "Stack size must be greater than 0");
private:
    uint32_t count = 0;
    std::array<ElementType, size> stack;

public:
    void init() {
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == size;
    }

    void push(ElementType element) {
        stack[count++] = element;
    }

    ElementType pop() {
        ElementType res =  stack[count - 1];
        count--;

        return res;
    }
};

#endif
