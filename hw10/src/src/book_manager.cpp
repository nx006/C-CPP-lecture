//
// Created by 이준선 on 2023/05/29.
//

#include <book_manager.hpp>
#include <iostream>

void BookManager::run() {
    bookIn();        // 입고
    searchByAuthor();// 저자 검색
    searchByYear();  // 년도로 검색
}

void BookManager::bookIn() {
    std::cout << "입고할 책을 입력하세요. 년도에 -1을 입력하면 입고를 종료합니다.\n";

    auto book_count = 0;

    while (true) {
        std::string title;
        std::string author;
        int publish_year = 0;

        std::cout << "년도>>";
        std::cin >> publish_year;

        if (publish_year == -1) {
            break;
        }

        std::cout << "책 제목>>";
        std::cin >> title;

        std::cout << "저자>>";
        std::cin >> author;

        v.emplace_back(title, author, publish_year);
        book_count++;
    }

    std::cout << "총 입고된 책은 " << book_count << "권입니다.\n";
}

void BookManager::searchByAuthor() const {
    std::cout << "검색하고자 하는 저자 이름을 입력하세요>>";

    std::string author;
    std::cin >> author;

    // linear search
    bool is_found = false;
    for (const auto &book: v) {
        if (book.getAuthor() == author) {
            is_found = true;
            book.show();
        }
    }

    if (!is_found) {
        std::cout << "검색 결과가 없습니다.\n";
    }
}

void BookManager::searchByYear() const {
    std::cout << "검색하고자 하는 년도를 입력하세요>>";

    int year = 0;
    std::cin >> year;

    // linear search
    bool is_found = false;
    for (const auto &book: v) {
        if (book.getYear() == year) {
            is_found = true;
            book.show();
        }
    }

    if (!is_found) {
        std::cout << "검색 결과가 없습니다.\n";
    }
}
