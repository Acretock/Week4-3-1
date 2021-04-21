#include <algorithm>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

int NOD(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (a != 0 && b != 0)
    {
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return a + b;
}


class Rational
{
private:
    int numerator;
    int denominator;

public:
	Rational();
	Rational(int num, int den);
	~Rational();

    int Numerator() const { return numerator; }
    int Denominator() const{ return denominator; }

    void Reverse() {
        int tmp = denominator;
        denominator = numerator;
        numerator = tmp;
    }

    void Check() {
        int n = NOD(numerator, denominator);
        if ((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0)) {
            numerator *= -1;
            denominator *= -1;
        }
        numerator /= n;
        denominator /= n;
        if (numerator == 0)
            denominator = 1;
    }

    const Rational operator*(Rational& r) const {
        int a = this->denominator * r.denominator;
        int b = this->numerator * r.numerator;
        Rational c(b, a);
        return c;
    }
    const Rational operator/(Rational& r) const {
        r.Reverse();
        int a = this->denominator * r.denominator;
        int b = this->numerator * r.numerator;
        Rational c(b, a);
        return c;
    }
    const Rational operator+(Rational r) const {
        int a = (this->numerator * r.denominator)
            + (r.numerator * this->denominator);
        int b = this->denominator * r.denominator;
        Rational c(a, b);
        return c;        
    }
    const Rational operator-(Rational r) const {
        int a = (this->numerator * r.denominator)
            - (r.numerator * this->denominator);
        int b = this->denominator * r.denominator;
        Rational c(a, b);
        return c;
    }
    const bool operator==(Rational r) {
        if ((this->denominator == r.denominator) && (this->numerator == r.numerator))
            return true;
        else return false;
    }
    friend std::ostream& operator<<(ostream& out, const Rational& r) { 
        out << r.numerator << '/' << r.denominator;
        return out;
    }
    friend istream& operator>> (istream& in, Rational& r) {
        char c;
        in >> r.numerator;
        in >> c;
        in >> r.denominator;
        r.Check();
        return in;
    }
};

Rational::Rational()
{
    numerator = 0;
    denominator = 1; 
}

Rational::Rational(int num, int den)
{
    int n = NOD(num, den);
    if ((num < 0 && den < 0) ||(num > 0 && den < 0)) {
        num *= -1;
        den *= -1;
    }
    numerator = num / n;
    denominator = den / n;
    if (num == 0)
        denominator = 1;
}
Rational::~Rational()
{
}


int main()
{
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
