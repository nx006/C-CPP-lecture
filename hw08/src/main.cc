// SPDX-FileCopyrightText: © 2023 Lee Jun Seon <limazero14@gmail.com>
// SPDX-License-Identifier: Apache-2.0

#include <stdexcept>
#include <string>
#include <cstring>
#include <iostream>

class BaseArray
{
  private:
    int capacity;
    int *mem;

  protected:
    explicit BaseArray(int capacity = 100);
    virtual ~BaseArray();
    void put(int index, int val);
    int get(int index);
    [[nodiscard]] int getCapacity() const;
    void putCapacity(int newCap);
    int *getMem();
    void putMem(int *start);
    void deleteMem();
};

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

class MyStack : public BaseArray
{
  public:
    explicit MyStack(int capacity = 100);
    ~MyStack() override = default;
    void push(int n);
    int pop();
    [[nodiscard]] int capacity() const;
    [[nodiscard]] int length() const;

  private:
    int tos; /// top of stack [index], initial value = -1
};

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

int main()
{
    using namespace std;
    MyStack mStack(1);
    int n;
    cout << "스택에 삽입할 5개의 정수를 입력하라>> ";
    for (int i = 0; i < 5; i++)
    {
        cin >> n;
        mStack.push(n); // 스택에 푸시
    }
    cout << "스택 용량:" << mStack.capacity() << ", 스택 크기:" << mStack.length() << endl;
    cout << "스택의 모든 원소를 팝하여 출력한다>> ";
    while (mStack.length() > 0)
    {
        int k = mStack.pop();
        cout << k << ' '; // 스택에서 팝
    }
    cout << "\n스택 용량:" << mStack.capacity() << ", 스택 크기:" << mStack.length() << endl;
}
