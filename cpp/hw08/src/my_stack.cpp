//
// Created by 이준선 on 2023/05/11.
//

#include "my_stack.hpp"
#include <cstring>
#include <stdexcept>

MyStack::MyStack(int capacity) : tos(-1)
{
    if (capacity <= 0)
    {
        throw std::invalid_argument("Capacity must be positive");
    }

    putCapacity(capacity);
    putMem(new int[static_cast<unsigned long>(capacity)]);
}

void MyStack::push(const int n)
{
    if (length() == getCapacity())
    { // If the stack is full
        int new_capacity = getCapacity() * 2;
        int *new_int_arr = new int[static_cast<unsigned long>(new_capacity)];
        memcpy(new_int_arr, getMem(), static_cast<unsigned long>(getCapacity()) * sizeof(int));
        putCapacity(new_capacity);
        deleteMem();
        putMem(new_int_arr);
    }
    put(++tos, n);
}
int MyStack::pop()
{
    if (tos < 0)
    {
        throw std::underflow_error("Stack is empty");
    }

    int retVal = get(tos--);

    // Reduce memory size when the stack is only 1/4 full
    if (tos + 1 <= getCapacity() / 4 && getCapacity() > 2)
    {
        int newCapacity = getCapacity() / 2;
        int *newMem = new int[static_cast<unsigned long>(newCapacity)];
        memcpy(newMem, getMem(), static_cast<unsigned long>(newCapacity) * sizeof(int));
        putCapacity(newCapacity);
        deleteMem();
        putMem(newMem);
    }

    return retVal;
}
int MyStack::capacity() const
{
    return getCapacity();
}
int MyStack::length() const
{
    return tos + 1;
}
