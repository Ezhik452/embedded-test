#ifndef _SIMPLE_STACK_H_
#define _SIMPLE_STACK_H_

#include <array>
#include <cstdint>
#include <iostream>

template<typename ElementType, size_t size>
class SimpleStack {
    static_assert(size > 0, "Stack size must be greater than 0");

private:
    size_t curCount = 0;
    std::array<ElementType, size> stack;

public:
    void init() {
        curCount = 0;
    }

    bool isEmpty() {
        return curCount == 0;
    }

    size_t count() const noexcept {
        return size - curCount;
    }

    bool isFull() {
        return curCount == size;
    }

    void push(ElementType element) {
        if (!isFull()) {
            stack[curCount++] = element;
        }
    }

    ElementType pop() {
        ElementType res{};
        if (!isEmpty()) {
            res = stack[curCount - 1];
            curCount--;
        }

        return res;
    }
};

#endif
