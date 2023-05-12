// SPDX-FileCopyrightText: © 2023 Lee Jun Seon <limazero14@gmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "base_array.hpp"

#include <stdexcept>
#include <string>

BaseArray::BaseArray(int capacity)
{
    this->capacity = capacity;
    this->mem = new int[static_cast<unsigned long>(capacity)];
}

BaseArray::~BaseArray()
{
    delete[] mem;
}

void BaseArray::put(int index, int val)
{
    if (index < 0 || index >= capacity)
    {
        const auto err_msg = "Out of range\nExpected range: 0 ~ " + std::to_string(capacity - 1) +
                             "\nActual index: " + std::to_string(index);
        throw std::out_of_range(err_msg);
    }
    mem[index] = val;
}

int BaseArray::get(int index)
{
    if (index < 0 || index >= capacity)
    {
        const auto err_msg = "Out of range\nExpected range: 0 ~ " + std::to_string(capacity - 1) +
                             "\nActual index: " + std::to_string(index);
        throw std::out_of_range(err_msg);
    }
    return mem[index];
}

int BaseArray::getCapacity() const
{
    return capacity;
}

void BaseArray::putCapacity(int newCap)
{
    capacity = newCap;
}

int *BaseArray::getMem()
{
    return mem;
}

void BaseArray::putMem(int *start)
{
    mem = start;
}

void BaseArray::deleteMem()
{
    delete[] mem;
}
