#include "rational.h"

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {
}

Rational::Rational(int numer, int denom) {
    if (denom == 0) {
        throw RationalDivisionByZero();
    }
    int gcd = std::gcd(numer, denom);
    if (denom < 0) {
        gcd = -gcd;
    }
    numer_ = numer / gcd;
    denom_ = denom / gcd;
}
void Rational::Reduce() {
    if (denom_ == 0) {
        throw RationalDivisionByZero();
    }
    int gcd = std::gcd(denom_, numer_);
    if (denom_ < 0) {
        gcd = -gcd;
    }
    denom_ /= gcd;
    numer_ /= gcd;
}
int Rational::GetDenominator() const {
    return denom_;
}

int Rational::GetNumerator() const {
    return numer_;
}

void Rational::SetDenominator(int value) {
    denom_ = value;
    Reduce();
}

void Rational::SetNumerator(int value) {
    numer_ = value;
    Reduce();
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero();
    }
    int64_t gcd = std::gcd(denom, numer);
    if (denom < 0) {
        gcd = -gcd;
    }
    denom /= gcd;
    numer /= gcd;
    denom_ = static_cast<int>(denom);
    numer_ = static_cast<int>(numer);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t numer = static_cast<int64_t>(lhs.numer_) * rhs.denom_ + static_cast<int64_t>(rhs.numer_) * lhs.denom_;
    int64_t denom = static_cast<int64_t>(lhs.denom_) * rhs.denom_;
    lhs.Set(numer, denom);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int64_t numer = static_cast<int64_t>(lhs.numer_) * rhs.numer_;
    int64_t denom = static_cast<int64_t>(lhs.denom_) * rhs.denom_;
    lhs.Set(numer, denom);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ += ratio.denom_;
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ -= ratio.denom_;
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    int numer = 0;
    int denom = 1;
    is >> numer;
    if (is.peek() == '/') {
        is.ignore(1);
        is >> denom;
    }
    ratio.Set(numer, denom);
    return is;
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += -rhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs.Set(static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator(),
            static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetNumerator());
    lhs.Reduce();
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational return_value = lhs;
    return_value += rhs;
    return return_value;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational return_value = lhs;
    return_value -= rhs;
    return return_value;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int64_t numer = static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetNumerator();
    int64_t denom = static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetDenominator();
    Rational l;
    l.Set(numer, denom);
    return l;
}

Rational operator++(Rational& ratio, int) {
    Rational copy_ratio = ratio;
    ratio.SetNumerator(ratio.GetNumerator() + ratio.GetDenominator());
    return copy_ratio;
}

Rational operator--(Rational& ratio, int) {
    Rational copy_ratio = ratio;
    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());
    return copy_ratio;
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        return os << ratio.GetNumerator();
    } else {
        return os << ratio.GetNumerator() << '/' << ratio.GetDenominator();
    }
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int64_t numer = static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator();
    int64_t denom = static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetNumerator();
    Rational l;
    l.Set(numer, denom);
    return l;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() <
           static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetNumerator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() >
           static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetNumerator();
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs or lhs == rhs;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs > rhs or lhs == rhs;
}