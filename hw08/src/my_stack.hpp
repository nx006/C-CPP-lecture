// SPDX-FileCopyrightText: © 2023 Lee Jun Seon <limazero14@gmail.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "base_array.hpp"

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
