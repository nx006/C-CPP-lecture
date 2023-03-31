#include <iostream>

class Sample
{
public:
    Sample(const int n) : capacity(n), size(0)
    {
        p = new int[n];
    }

    void read();
    void write() const;
    int big();
    int getSize() const
    {
        return size;
    }
    ~Sample()
    {
        delete[] p;
    }

private:
    int *p;
    int capacity;
    int size;
};

void Sample::read()
{
    std::cout << "입력할려는 정수의 갯수는 ? ";
    std::cin >> size;
    std::cout << size << "개의 정수를 입력하시오 ";
    for (auto idx = 0; idx < size; idx++)
    {
        std::cin >> p[idx];
    }
}

void Sample::write() const
{
    for (auto idx = 0; idx < size; idx++)
    {
        std::cout << p[idx] << ' ';
    }
    std::cout << std::endl;
}

int Sample::big()
{
    auto firstIterator = p;
    const auto lastIterator = p + size;
    if (firstIterator != lastIterator)
    {
        auto currentIterator = firstIterator;
        while (++currentIterator != lastIterator)
        {
            if (*firstIterator < *currentIterator)
            {
                firstIterator = currentIterator;
            }
        }
    }
    return *firstIterator;
}

int main()
{
    Sample s(10);
    s.read();
    std::cout << "동적 배열 정수 " << s.getSize() << "개를 출력합니다.";
    s.write();
    std::cout << "가장 큰 수는 " << s.big() << std::endl;
}