#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Circle
{
  public:
    Circle(int radius_ = 1, std::string name_ = "") : name(std::move(name_)), radius(radius_)
    {
    }
    constexpr double getArea() const
    {
        return 3.14 * radius * radius;
    }
    std::string getName() const
    {
        return name;
    }
    bool operator<(const Circle &b) const;
    friend std::ostream &operator<<(std::ostream &os, const std::vector<Circle> &b);

  private:
    std::string name;
    int radius;
};

bool Circle::operator<(const Circle &b) const
{
    return this->getArea() < b.getArea();
}

std::ostream &operator<<(std::ostream &os, const std::vector<Circle> &b)
{
    os << "모든 원소를 출력한다.>>";
    for (const auto &circle : b)
    {
        os << circle.getName() << ' ';
    }

    return os;
}

void printVector(const std::vector<Circle> &v)
{
    std::cout << v << std::endl;
}

int main()
{
    std::vector<Circle> v;
    v.emplace_back(Circle{2, "waffle"});
    v.emplace_back(Circle{3, "pizza"});
    v.emplace_back(Circle{1, "dotnet"});
    v.emplace_back(Circle{5, "pizzsLarge"});
    printVector(v);
    const auto it = v.size() - 1;
    std::sort(&v[0], &v[it]);
    printVector(v);
    std::cout << std::endl << "프랜드 함수 operator<<로 출력하는 경우" << std::endl;
    std::cout << v << std::endl;
}
