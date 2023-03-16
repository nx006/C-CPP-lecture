#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

class StringManager
{
public:
    StringManager() = default;
    ~StringManager() = default;

    void printMenu() const {
        std::cout << "영문 텍스트를 입력하세요. 히스토그램을 그립니다." << std::endl;
        std::cout << "텍스트의 끝은 "<< endChar << " 입니다. " << maximumCount << "개까지 가능합니다." << std::endl;
    }

    void getString() {
        std::string input;
        std::getline(std::cin, input, endChar);
        this->input = input.substr(0, maximumCount);

        for (const auto c : input) {
            if (std::isalpha(c)) {
                alphabetCount++;
            }
        }
    }


    auto createHistogram() {
        for (const auto c : input) {
            if (std::isalpha(c)) {
                histogram[c]++;
            }
        }
    }

    const auto& getHistogram() const {
        return histogram;
    }

    int getAlphabetCount() const {
        return alphabetCount;
    }

    void printHistogram() {
        for (char c = 'a'; c <= 'z'; c++) {
            _drawBar(c);
        }
    }

    void printStatus() const {
        std::cout << "총 알파벳 수 " << getAlphabetCount() << std::endl;
    }

    void toLower() {
        for (auto& c : input) {
            c = std::tolower(c);
        }
    }

private:
    std::string input;
    int maximumCount = 10000;
    char endChar = ';';
    int alphabetCount = 0;
    std::unordered_map<char, int> histogram;

    void _drawBar(const char c) {
        std::cout << c << " (" << histogram[c] << ")\t: ";
        for (std::size_t i = 0; i < histogram[c]; i++) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
};

int main()
{
    StringManager manager;
    manager.printMenu();
    manager.getString();
    manager.toLower();
    manager.createHistogram();
    manager.printStatus();
    manager.printHistogram();

    return 0;
}