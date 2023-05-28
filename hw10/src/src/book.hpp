//
// Created by 이준선 on 2023/05/29.
//

#pragma once
#include <string>
#include <utility>

using namespace std;
class Book {
    string title; // 책 이름
    string author;// 저자
    int year = 0;

public:
    Book()= default;;
    Book(string _title, string _author, int _year) {
        this->title = std::move(_title);
        this->author = std::move(_author);
        this->year = _year;
    }
    void set(string _title, string _author, int _year) {
        this->title = std::move(_title);
        this->author = std::move(_author);
        this->year = _year;
    }
    [[nodiscard]] string getAuthor() const { return author; }
    [[nodiscard]] int getYear() const { return year; }
    void show() const;
};
