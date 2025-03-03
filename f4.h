#ifndef F4_H
#define F4_H

#include <iostream>

struct F4 {
    int value = 0;

    F4(long long v = 0) { value = v % 4; }

    static constexpr int addition_table[4][4] = {
        {0, 1, 2, 3},
        {1, 0, 3, 2},
        {2, 3, 0, 1},
        {3, 2, 1, 0},
    };
    friend F4 operator+(F4 const a, F4 const b)
    {
        F4 result;
        result.value = addition_table[a.value][b.value];
        return result;
    }
    F4& operator+=(F4 const& b)
    {
        this->value = (*this + b).value;
        return *this;
    }
    friend F4 operator-(F4 const a, F4 const b)
    {
        return a + b;
    }
    F4& operator-=(F4 const& b)
    {
        this->value = (*this - b).value;
        return *this;
    }

    static constexpr int multiplication_table[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 2, 3},
        {0, 2, 3, 1},
        {0, 3, 1, 2},
    };
    friend F4 operator*(F4 const a, F4 const b)
    {
        F4 result;
        result.value = multiplication_table[a.value][b.value];
        return result;
    }
    F4& operator*=(F4 const& b)
    {
        this->value = (*this * b).value;
        return *this;
    }

    static constexpr int division_table[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 3, 2},
        {0, 2, 1, 3},
        {0, 3, 2, 1},
    };
    friend F4 operator/(F4 const a, F4 const b)
    {
        F4 result;
        result.value = division_table[a.value][b.value];
        return result;
    }
    F4& operator/=(F4 const& b)
    {
        this->value = (*this / b).value;
        return *this;
    }


    friend F4 mexp(F4 a, long long e)
    {
        F4 res = 1;
        while (e) {
            if (e & 1)
                res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, F4 const& a)
    {
        switch (a.value) {
            case 0:
                return os << '0';
            case 1:
                return os << '1';
            case 2:
                return os << 'a';
            case 3:
                return os << "1+a";
            default:
                break;
        }
        return os;
    }
    friend bool operator==(F4 const& a, F4 const& b) { return a.value == b.value; }
    friend bool operator!=(F4 const& a, F4 const& b) { return a.value != b.value; }
    friend bool operator<(F4 const& a, F4 const& b) {return a.value < b.value; }
};

#endif
