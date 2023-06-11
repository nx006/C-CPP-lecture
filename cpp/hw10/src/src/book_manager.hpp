//
// Created by 이준선 on 2023/05/29.
//

#pragma once
#include <book.hpp>
#include <vector>

class BookManager {
public:
    void run();

private:
    vector<Book> v;

private:
    void searchByAuthor() const;
    void searchByYear() const;
    void bookIn();
};