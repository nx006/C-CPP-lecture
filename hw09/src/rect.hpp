//
// Created by 이준선 on 2023/05/22.
//

#pragma once
#include <shape.hpp>

class Rect : public Shape {
public:
    Rect(string n = "", int w = 0, int h = 0) : Shape(std::move(n), w, h) {}
    ~Rect() override = default;
    constexpr double getArea() const override { return width * height; }
};
