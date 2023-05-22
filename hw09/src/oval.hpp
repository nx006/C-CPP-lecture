//
// Created by 이준선 on 2023/05/22.
//

#pragma once
#include <shape.hpp>

class Oval : public Shape {
public:
    Oval(string n = "", int w = 0, int h = 0) : Shape(std::move(n), w, h) {}
    ~Oval() override = default;
    constexpr double getArea() const override { return PI * width * height; }

private:
    static constexpr auto PI = 3.14;
};
