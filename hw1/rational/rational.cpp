#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>
// Libraries may be included as necessary

using namespace std;


Rational::Rational() : n(0), d(1) {}

Rational::Rational(int n, int d) {
    // Since the denominator cannot be zero an exception is thrown
    if (d == 0) {
        throw std::invalid_argument("division by zero");
    }
    this->n = n;
    this->d = d;
    reduce();
    normalize();
    // TODO: continue your implementation below.
    // You should likely set the member variables ad then call this->reduce()
    // and this->normalize().
    
}
void Rational::reduce()
{
    int gcd;
    int smol;
    int de = this->d;
    int nu = this->n;
    bool nuneg = false;
    bool deneg = false;
    if (nu < 0)
    {
        nu = abs(nu);
        nuneg = true;
    }
    if (de < 0)
    {
        de = abs(de);
        deneg = true;
    }
    if (nu > de)
        smol = de;
    else
        smol = nu;
    for (int i = 1; i <= smol; i++)
    {
        if (nu % i == 0 && de % i == 0)
            gcd = i;
    }
    if (nuneg)
    {
        nu = nu / gcd;
        int temp;
        temp = nu;
        temp *= 2;
        nu = nu - temp;
        this->n = nu;
    }
    else
    {
        this->n = nu / gcd;
    }
    if (deneg)
    {
        de = de / gcd;
        int temp;
        temp = de;
        temp *= 2;
        de = de - temp;
        this->d = de;
    }
    else
    {
        this->d = de/gcd;
    }
}
void Rational::normalize() {

    if (n == 0 && d != 1) {
        d = 1;
    }
}
ostream& operator<<(std::ostream& out, const Rational& r)
{

    if (r.n < 0 && r.d < 0)
    {
        out << abs(r.n) << "/" << abs(r.d);
    }
    else if (r.n < 0 || r.d < 0)
    {
        out << "-" << abs(r.n) << "/" << abs(r.d);
    }
    else
    {
        out << r.n << "/" << r.d;
    }
    return out;
}

// istream extraction operator: '>>'
//
// When inputting a Rational, read a numerator, a '/', and a denominator
// and set the Rational input reference with the appropriate value
// specified by the values read.
//
// Any amount of whitespace may separate numerator, '/', and denominator.
// The numerator and/or denominator may be negative when read.
istream& operator>>(std::istream& in, Rational& r)
{
    
    char slash;
    in >> r.n >> slash >> r.d;
    r.reduce();
    return in;
}

// Add additional function prototypes here. You can discern what additional
// prototypes are needed by studying rational_test.cpp and figuring out
// what function call is needed for each rational operation. Use that
// exercise as a checklist for the prototypes that need to be added here
// and implemented. Only use the friend keyword if it's necessary. Some
// examples are provided.

// Add a rational number to another one, returning a new Rational.
//Rational operator+(const Rational& rhs) const;

// Addition assignment returns a reference to this (*this) and is not const
// because it modifies this.
//Rational& operator+=(const Rational& rhs);

// We can use a similar pattern for operations with integers.
//Rational operator*(int rhs) const;

// If you need to write an operator where the non-rational is on the left
// side, you need to override the global multiplication operator. Since
// that function will need to reference private members on rhs, which is
// a Rational, we have to declare it as a friend in the Rational
// declaration.

 Rational operator+(int lhs, const Rational& rhs)
{
    Rational result;
    result.n = lhs*rhs.d + rhs.n;
    result.d = rhs.d;
    result.reduce();
    return result;
}
// Comparison operators are fairly straightforward. Note that you can
// invoke another operator in your operator definition, just make sure you
// don't end up creating an infinite recursive loop.
//bool operator==(const Rational& other) const;
Rational Rational::operator+(const Rational& rhs) const {
    Rational result;
    result.d = this->d * rhs.d;
    result.n = (this->n * rhs.d) + (this->d * rhs.n);
    result.reduce();
    return result;
}
Rational Rational::operator^(int rhs) const {
    Rational result;
    result.n = this->n;
    result.d = this->d;
    bool neg = false;
    if (rhs == 0)
    {
        result.n = 1;
        result.d = 1;
        return result;
    }
    if (rhs < 0)
    {
        neg = true;
        rhs = abs(rhs);
    }
    for (int i = 1; i < rhs; i++)
    {
        result.n *= this->n;
        result.d *= this->d;
    }
    if (neg)
    {
        int temp = result.n;
        result.n = result.d;
        result.d = temp;
    }
    result.reduce();
    return result;
}
Rational Rational::operator+(int rhs) const {
    Rational result;
    result.d = this->d;
    result.n = this->n + (this->d*rhs);
    result.reduce();
    return result;
}
Rational& Rational::operator+=(const Rational& rhs) {
    int temp = this->d;
    this->d = this->d * rhs.d;
    this->n = (this->n * rhs.d) + (temp * rhs.n);
    this->reduce();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
    this->d = this->d * rhs.d;
    this->n = (this->n * rhs.n);
    this->reduce();
    return *this;
}
Rational& Rational::operator*=(int rhs) {
    this->d = this->d;
    this->n = this->n* rhs;
    this->reduce();
    return *this;
}
Rational& Rational::operator+=(int rhs)  {
    this->d = this->d;
    this->n = this->n + (this->d * rhs);
    this->reduce();
    return *this;
}
Rational Rational::operator*(int rhs) const {
    Rational result;
    result.d = this->d;
    result.n = this->n * rhs;
    result.reduce();
    return result;
}

// This operator isn't prefixed by Rational:: because it's not actually a
// member of Rational. It just tells the compiler what to do when it sees
// multiplication between an int on the left and a Rational on the right. Our
// friend declaration simply enabled us to access private members on the const
// Rational& rhs in the function body.
//
// Note that we could implement any of the other operators above this same way
// using the corresponding global operator and passing a const Rational& lhs as
// the first argument, it's just a matter of convenience.
Rational operator*(int lhs, const Rational& rhs) {
    Rational result;
    result.d = rhs.d;
    result.n = rhs.n*lhs;
    result.reduce();
    return result;
}
Rational Rational::operator*(const Rational& rhs) const {
    Rational result;
    result.d = this->d * rhs.d;
    result.n = this->n * rhs.n;
    result.reduce();
    return result;
}
bool Rational::operator<(const Rational& rhs) const {
    Rational result;
    if (this->n > 0 && this->d > 0 && rhs.n > 0 && rhs.d > 0)
    {
        if ((this->n * rhs.d) - (this->d * rhs.n) < 0)
            return true;
        else
            return false;
    }
    if (this->n < 0 && this->d > 0 && rhs.n > 0 && rhs.d > 0)
    {
        return true;
    }
    if (this->n > 0 && this->d < 0 && rhs.n > 0 && rhs.d > 0)
    {
        return true;
    }
    if (this->n < 0 && this->d > 0 && rhs.n < 0 && rhs.d > 0)
    {
        return false;
    }
    if (this->n < 0 && this->d > 0 && rhs.n > 0 && rhs.d < 0)
    {
        return false;
    }
    if (this->n < 0 && this->d > 0 && rhs.n < 0 && rhs.d < 0)
    {
        return true;
    }
    if (this->n > 0 && this->d < 0 && rhs.n < 0 && rhs.d < 0)
    {
        return true;
    }
}
bool Rational::operator==(const Rational& other) const {
    if (this->n == other.n && this->d == other.d)
        return true;
    else
        return false;
}
bool Rational::operator!=(const Rational& other) const {
    if (this->n != other.n || this->d != other.d)
        return true;
    else
        return false;
}

// TODO: implement the rest of your prototyped methods
