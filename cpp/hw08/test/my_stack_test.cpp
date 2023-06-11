// SPDX-FileCopyrightText: © 2023 Lee Jun Seon <limazero14@gmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "../src/my_stack.hpp"

#include <gtest/gtest.h>

namespace
{
class MyStackTest : public ::testing::Test
{
  protected:
    MyStackTest() = default;
    ~MyStackTest() override = default;
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
};

TEST_F(MyStackTest, Constructor)
{
    MyStack stack(10);
    EXPECT_EQ(stack.capacity(), 10);
    EXPECT_EQ(stack.length(), 0);
}

TEST_F(MyStackTest, DefaultConstructor)
{
    MyStack stack;
    EXPECT_EQ(stack.capacity(), 100);
    EXPECT_EQ(stack.length(), 0);
}

TEST_F(MyStackTest, NoNegativeOrZeroCapacity)
{
    EXPECT_THROW(MyStack stack(-1), std::invalid_argument);
    EXPECT_THROW(MyStack stack(0), std::invalid_argument);
}

TEST_F(MyStackTest, PushAndPop)
{
    MyStack stack(10);
    stack.push(1);
    EXPECT_EQ(stack.length(), 1);
    EXPECT_EQ(stack.pop(), 1);
    EXPECT_EQ(stack.length(), 0);
}

TEST_F(MyStackTest, PopInEmptyStack)
{
    MyStack stack(10);
    EXPECT_THROW(stack.pop(), std::underflow_error);
}

TEST_F(MyStackTest, PushAndPopMultiple)
{
    MyStack stack(10);
    for (int i = 0; i < 10; i++)
    {
        stack.push(i);
    }
    EXPECT_EQ(stack.length(), 10);
    for (int i = 9; i >= 0; i--)
    {
        EXPECT_EQ(stack.pop(), i);
    }
    EXPECT_EQ(stack.length(), 0);
}

TEST_F(MyStackTest, PushMoreThanCapacity)
{
    MyStack stack(4);
    for (int i = 0; i < 4; i++)
    {
        stack.push(i);
    }
    EXPECT_EQ(stack.length(), 4);
    stack.push(4);
    EXPECT_EQ(stack.length(), 5);
    EXPECT_EQ(stack.capacity(), 8);
}

TEST_F(MyStackTest, PopAndCapacity)
{
    MyStack stack(8);
    for (int i = 0; i < 8; i++)
    {
        stack.push(i);
    }

    for (int i = 0; i < 6; i++)
    {
        stack.pop();
    }

    EXPECT_EQ(stack.length(), 2);
    EXPECT_EQ(stack.capacity(), 4);

    EXPECT_EQ(stack.pop(), 1);
    EXPECT_EQ(stack.length(), 1);
    EXPECT_EQ(stack.capacity(), 2);
}

TEST_F(MyStackTest, PushAndPopMain)
{
    MyStack stack(8);
    for (int i = 0; i < 5; i++)
    {
        stack.push(i);
    }

    EXPECT_EQ(stack.capacity(), 8);
    EXPECT_EQ(stack.length(), 5);
    for (int i = 0; i < 5; i++)
    {
        stack.pop();
    }

    EXPECT_EQ(stack.capacity(), 2);
    EXPECT_EQ(stack.length(), 0);
}

TEST_F(MyStackTest, keepPushAndPop)
{
    MyStack stack(1);
    for (int i = 0; i < 100; i++)
    {
        stack.push(i);
        EXPECT_EQ(stack.length(), 1);
        EXPECT_EQ(stack.capacity(), 1);
        EXPECT_EQ(stack.pop(), i);
    }
}
} // namespace