// SPDX-FileCopyrightText: © 2023 Lee Jun Seon <limazero14@gmail.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

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
