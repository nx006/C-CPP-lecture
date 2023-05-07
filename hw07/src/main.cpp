#include <iostream>

using std::ostream;

class Complex
{
  private:
    double re;
    double im;

  public:
    Complex(double _real) : re(_real), im(0)
    {
    }
    Complex(double _real = 0, double _imaginary = 0) : re(_real), im(_imaginary)
    {
    }
    void Output()
    {
        std::cout << re << " + " << im << "i" << std::endl;
    }

    Complex &operator+=(Complex);
    Complex &operator-();
    friend Complex operator+(Complex &, Complex &);
    friend Complex operator++(Complex &);
    friend Complex operator++(Complex &, int);
    friend ostream &operator<<(ostream &os, Complex &);
};

Complex &Complex::operator+=(Complex rhs)
{
    re += rhs.re;
    im += rhs.im;
    return *this;
}

Complex &Complex::operator-()
{
    re = -re;
    im = -im;
    return *this;
}

Complex operator+(const Complex &lhs, const Complex &rhs)
{
    Complex temp(lhs);
    temp += rhs;
    return temp;
}

Complex operator++(Complex &rhs)
{
    rhs.re++;
    rhs.im++;
    return rhs;
}

Complex operator++(Complex &rhs, int)
{
    Complex temp(rhs);
    rhs.re++;
    rhs.im++;
    return temp;
}

std::ostream &operator<<(std::ostream &os, Complex &rhs)
{
    os << "(" << rhs.re << " + " << rhs.im << "i"
       << ")" << std::endl;
    return os;
}

int main()
{
    Complex c1(1, 2), c2(3, 4), c(9, 200);
    c1.Output();
    c2.Output();
    c1 += c2;
    c1.Output();
    Complex c3 = c1 + c2;
    Complex c4 = c1 += c2, c5, c6;
    c3.Output();
    c5 = ++c4;
    c4.Output();
    c5.Output();
    c6 = c4++;
    c4.Output();
    c6.Output();
    c2 = -c2;
    std::cout << c2;
    std::cout << c;
    return 0;
}