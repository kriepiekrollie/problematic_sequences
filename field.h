#ifndef FIELD_H
#define FIELD_H

#include <iostream>

extern int MOD;
struct element {

    int value;

    element(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
    element(long long a, long long b) : value(0) { *this += a; *this /= b;}

    element& operator+=(element const& b) { value += b.value; if (value >= MOD) value -= MOD; return *this; }
    element& operator-=(element const& b) { value -= b.value; if (value < 0) value += MOD;return *this; }
    element& operator*=(element const& b) { value = (long long)value * b.value % MOD;return *this; }

    friend element mexp(element a, long long e)
    {
        element res = 1;
        while (e) {
            if (e & 1)
                res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }
    friend element inverse(element a) { return mexp(a, MOD - 2); }

    element& operator/=(element const& b) { return *this *= inverse(b); }
    friend element operator+(element a, element const b) { return a += b; }
    friend element operator-(element a, element const b) { return a -= b; }
    friend element operator-(element const a) { return 0 - a; }
    friend element operator*(element a, element const b) { return a *= b; }
    friend element operator/(element a, element const b) { return a /= b; }
    friend std::ostream& operator<<(std::ostream& os, element const& a) { return os << a.value; }
    friend bool operator==(element const& a, element const& b) { return a.value == b.value; }
    friend bool operator!=(element const& a, element const& b) { return a.value != b.value; }
    friend bool operator<(element const& a, element const& b) {return a.value < b.value; }
};

#endif
