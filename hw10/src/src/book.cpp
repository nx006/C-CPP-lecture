//
// Created by 이준선 on 2023/05/29.
//

#include <book.hpp>

#include <iostream>

void Book::show() const {
    cout << year << "년도, " << title << ", " << author << endl;
}
