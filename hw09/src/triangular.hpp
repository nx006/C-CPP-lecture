//
// Created by 이준선 on 2023/05/22.
//

#pragma once
#include <shape.hpp>

class Triangular : public Shape {
public:
    Triangular(string n = "", int w = 0, int h = 0) : Shape(std::move(n), w, h) {}
    ~Triangular() override = default;
    constexpr double getArea() const override { return width * height / 2; }
};
