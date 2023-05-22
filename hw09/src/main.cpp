#include <iostream>

#include <oval.hpp>
#include <rect.hpp>
#include <triangular.hpp>
#include <memory>

int main() {
    std::vector<std::unique_ptr<Shape>> p(3);
    p[0] = std::make_unique<Oval>("빈대떡", 10, 20);
    p[1] = std::make_unique<Rect>("찰떡", 30, 40);
    p[2] = std::make_unique<Triangular>("토스트", 30, 40);
    for (const auto & i : p)
        cout << i->getName() << " 넓이는 " << i->getArea() << endl;
}
