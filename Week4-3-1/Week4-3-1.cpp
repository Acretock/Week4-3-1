// Week4-3-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <set>
#include <map>
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
    pair<int, int> number;
    pair<int, int> *numbers;

public:
	Rational();
	Rational(int num, int den);
    Rational(pair<int,int> n);
	~Rational();
    //denomintator == num.second
    // numerator == num.first
    int Numerator() const { return number.first; }
    int Denominator() const{ return number.second; }

    void Reverse() {
        int tmp = number.second;
        number.second = number.first;
        number.first = tmp;
    }

    void Check() {
        int n = NOD(number.first, number.second);
        if ((number.first < 0 && number.second < 0) || (number.first > 0 && number.second < 0)) {
            number.first *= -1;
            number.second *= -1;
        }
        number.first /= n;
        number.second /= n;
        if (number.first == 0)
            number.second = 1;
    }

    const Rational operator*(Rational& r) const {
        int a = this->number.second * r.number.second;
        int b = this->number.first * r.number.first;
        Rational c(b, a);
        return c;
    }
    const Rational operator/(Rational& r) const {
        r.Reverse();
        int a = this->number.second * r.number.second;
        int b = this->number.first * r.number.first;
        Rational c(b, a);
        return c;
    }
    const Rational operator+(Rational r) const {
        int a = (this->number.first * r.number.second)
            + (r.number.first * this->number.second);
        int b = this->number.second * r.number.second;
        Rational c(a, b);
        return c;        
    }
    const Rational operator-(Rational r) const {
        int a = (this->number.first * r.number.second)
            - (r.number.first * this->number.second);
        int b = this->number.second * r.number.second;
        Rational c(a, b);
        return c;
    }
    const bool operator==(Rational r) {
        if ((this->number.second == r.number.second) && (this->number.first == r.number.first))
            return true;
        else return false;
    }
    friend std::ostream& operator<<(ostream& out, const Rational& r) { 
        out << r.number.first << '/' << r.number.second;
        return out;
    }
    friend istream& operator>> (istream& in, Rational& r) {
        char c;
        in >> r.number.first;
        in >> c;
        in >> r.number.second;
        r.Check();
        return in;
    }
    Rational operator=(Rational r) {
        this->number.first = r.number.first;
        this->number.second = r.number.second;
    }
    friend vector<>
    const bool operator<(const Rational& r) const {
        if (this->number.second == r.number.second)
            return (this->number.first < r.number.first);
        else
            return ((this->number.first * r.number.second) < (r.number.first * this->number.second));
     }

    const Rational operator[](int position) const {
        //Rational a(number.first, number.second);
        return (this[position]);
    }
    Rational operator[](int position) {
        //Rational a(number.first, number.second);
        return (this[position]);
    }

    //Rational push_back(pair<int, int>& p) {

   // }
};

Rational::Rational()
{
    number.first = 0;
    number.second = 1;
}

Rational::Rational(int num, int den)
{
    int n = NOD(num, den);
    if ((num < 0 && den < 0) ||(num > 0 && den < 0)) {
        num *= -1;
        den *= -1;
    }
    number.first = num / n;
    number.second = den / n;
    if (num == 0)
        number.second = 1;
}
Rational::Rational(pair<int,int> n)
{
    int nod = NOD(n.first, n.second);
    if ((n.first < 0 && n.second < 0) || (n.first > 0 && n.second < 0)) {
        n.first *= -1;
        n.second *= -1;
    }
    number.first = n.first/ nod;
    number.second = n.second / nod;
    if (n.first == 0)
        number.second = 1;
}
Rational::~Rational()
{
}


int main()
{
    {
        const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }



    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
