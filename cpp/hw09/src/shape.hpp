//
// Created by 이준선 on 2023/05/22.
//

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Shape {
protected:
    string name;      // 도형의 이름
    int width, height;// 도형이 내접하는 사각형
public:
    Shape(string n = "", int w = 0, int h = 0) {
        name = std::move(n);
        width = w;
        height = h;
    }
    virtual ~Shape() = default;
    virtual double getArea() const { return 0; }
    string getName() const { return name; }// 이름 리턴
};