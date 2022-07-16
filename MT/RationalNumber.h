/* RationalNumber */
#ifndef RATIONAL_NUMBER_H
#define RATIONAL_NUMBER_H

#include "excep.h"

class RationalNumber;

class RationalNumber {
    long long numerator;   // above 
    long long denominator; // below
    char *numstr = 0;
    char* toString();
public:
    RationalNumber() {};
    RationalNumber(long long num) : numerator(num), denominator(1) {};
    RationalNumber(long long num, long long den);
    RationalNumber(const RationalNumber &num) : numerator(num.numerator), 
                                    denominator(num.denominator) {};
    ~RationalNumber() { delete[] numstr; }
    

    long long getNum() const { return numerator; }
    long long getDen() const { return denominator; }

    RationalNumber operator+(const RationalNumber &num);
    RationalNumber operator-(const RationalNumber &num);
    RationalNumber operator*(const RationalNumber &num);
    RationalNumber operator/(const RationalNumber &num);

    RationalNumber operator=(const RationalNumber &num);
    bool operator==(const RationalNumber &num);

    RationalNumber operator+=(const RationalNumber &num);
    RationalNumber operator-=(const RationalNumber &num);
    RationalNumber operator*=(const RationalNumber &num);
    RationalNumber operator/=(const RationalNumber &num);

    const char* getstr();
    void set(const char *s);

    static long long get_prime(unsigned idx);
    static bool is_prime(long long num);
private:
    void normalize();
};


class rn_excep : public excep {
protected:
    using excep::Exception::set_mes;
public:
    rn_excep() : excep() {}
    rn_excep(const rn_excep &ex) : excep(ex) {}
    rn_excep(const ex_type t) : excep() { set_mes(t); }

    void set_mes(const ex_type t)
    {
        type = t;
        switch(t) {
            case DZ:
                set_mes("RationalNumber: dividing by zero");
                break;
            case NG:
                set_mes("RationalNumber: negative index");
                break;
            case BS:
                set_mes("RationalNumber: bad string");
                break;
            default:
                set_mes("RationalNumber: error");
                break;
        }
    }

    ~rn_excep() {}
};


#endif
