#include "../MT/RationalNumber.h"
#include "../MT/str.h"

typedef long long ll;
typedef RationalNumber rn;

//char *RationalNumber::numstr = 0;

RationalNumber::RationalNumber(ll num, ll den) : numerator(num), denominator(den)
{
    if(denominator == 0)
        throw rn_excep(DZ);
    normalize();
}

rn RationalNumber::operator+(const rn &num)
{
    rn tmp(numerator*num.denominator+num.numerator*denominator,
           denominator*num.denominator);
    tmp.normalize();
    return tmp;
}


rn RationalNumber::operator-(const rn &num)
{
    rn tmp(numerator*num.denominator-num.numerator*denominator,
           denominator*num.denominator);
    tmp.normalize();
    return tmp;
}


rn RationalNumber::operator*(const rn &num)
{
    rn tmp(numerator*num.numerator,
           denominator*num.denominator);
    tmp.normalize();
    return tmp;
}

rn RationalNumber::operator/(const rn &num)
{
    if(num.numerator == 0) 
        throw rn_excep(DZ);
    rn tmp(numerator*num.denominator,
           denominator*num.numerator);
    tmp.normalize();
    return tmp;
}

rn RationalNumber::operator=(const rn &num)
{
    numerator = num.numerator;
    denominator = num.denominator;
    return *this;
}

bool RationalNumber::operator==(const rn &num)
{
    return (numerator == num.numerator) && (denominator == num.denominator);
}

rn RationalNumber::operator+=(const rn &num)
{
    return *this = *this + num;
}

rn RationalNumber::operator-=(const rn &num)
{ 
    return *this = *this - num;
}

rn RationalNumber::operator*=(const rn &num)
{
    return *this = *this * num;
}

rn RationalNumber::operator/=(const rn &num)
{
    return *this = *this / num;
}

char* RationalNumber::toString()
{
    char buf[50];
    numToStr(numerator, buf);
    int s = strsize(buf);
    if(denominator != 1) {
        cpystr("/", buf + s);
        numToStr(denominator, buf+s+1);
        s = strsize(buf);
    }
    char *tmp = new char[s+1];
    cpystr(buf, tmp);
    return tmp;
}

const char* RationalNumber::getstr()
{
    if(numstr)
        delete[] numstr;
    numstr = toString();
    return numstr;
}

void RationalNumber::set(const char *s)
{
    int j = 0;
    int n = 0;
    char *str = cpystr(s);
try { 
    denominator = 1;
    if(str[j] != '-' && (str[j] < '0' || str[j] > '9'))
        throw rn_excep(BS);
    j++;
    while(str[j] != 0 && str[j] != '/') {
        if(str[j] < '0' || str[j] > '9')
            throw rn_excep(BS);
        j++;
    }
    if(str[j] == '/') {
        str[j] = 0;
        j++;
        n=j;
    }
    
    strToNum(str, numerator);

    if(n) {
        if(str[j] != '-' && (str[j] < '0' || str[j] > '9'))
            throw rn_excep(BS);
        j++;
        while(str[j] != 0) {
            if(str[j] < '0' || str[j] > '9') 
                throw rn_excep(BS);
            j++;
        }
        strToNum(str+n, denominator);
    }

}

catch(...) {
    delete[] str;
    throw ;
}
    normalize();
    delete[] str;     
}


/*
ll RationalNumber::get_prime(unsigned idx)
{
    const ll primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 
                     29, 31, 37, 41, 43, 47, 53, 59, 
                     61, 67, 71, 73, 79, 83, 89, 97 };
    unsigned elems = sizeof(primes)/sizeof(ll);
    if(idx < elems)
        return primes[idx];
    idx -= elems;
    ll num = primes[elems-1] + 1;
    while(true) {
        if(is_prime(num)) {
            if(idx == 0)
                return num;
            idx--;
        }
        num++;
    }
}
*/

/*
bool RationalNumber::is_prime(ll num)
{
    if(num <= 0)
        throw rn_excep(NG);
    else if(num == 1)
        return true;
    ll half = num/2;
    ll pr;
    ll idx = 0;
    while((pr = get_prime(idx)) <= half) {
        if(num % pr == 0)
            return false;
        idx++;
    }
    return true;
}
*/

void RationalNumber::normalize()
{
    if(numerator == 0) {
        denominator = 1;
        return ;
    }
    if(denominator == 0)
        throw rn_excep(DZ);

    if(denominator < 0) {
        denominator *= -1;
        numerator *= -1;
    }

    ll tmp = numerator > 0 ? numerator : -numerator;
    ll max = tmp;
    ll min = denominator;
    if(max < min) {
        max = min;
        min = tmp;
    }
    while(max % min != 0) {
        tmp = min;
        min = max % min;
        max = tmp;
    }
    numerator /= min;
    denominator /= min;

/*
    ll pr;
    ll idx = 0;
    int till = 100;
    while(((pr = get_prime(idx)) <= min/2) && till > 0) {
       while((numerator % pr == 0) && (denominator % pr == 0)) {
           numerator /= pr;
           denominator /= pr;
           tmp = numerator > 0 ? numerator : -numerator;
           min = tmp < denominator ? tmp : denominator;
       }
       till--;
       idx++;
    }

    if(numerator % denominator == 0) {
        numerator /= denominator;
        denominator = 1;
    } else if(denominator % numerator == 0) {
        denominator /= numerator;
        numerator = 1;
    }
*/
}

/*
rn_excep::rn_excep(const rn_ex_type t) : Exception(), type(t)
{
    set_mes(t);
}   

void rn_excep::set_mes(const rn_ex_type t)
{
    type = t;
    switch(t) {
        case DZ:
            set_mes("RationalNumber: dividing by zero");
            break;
        case NG:
            set_mes("RationalNumber: negative index");
            break;
    }
}

rn_excep rn_excep::operator=(const rn_excep &ex)
{
    Exception::operator=(ex);
    type = ex.type;
    return *this;
}
*/
/*
#ifdef OSTREAM
std::ostream& operator<<(std::ostream& os, const rn &num)
{   
    if(num.getDen() == 1 || num.getNum() == 0) 
        os << num.getNum();
    else
        os << num.getNum() << "/" << num.getDen();
    return os;
}



#endif
*/
/*
int main()
{
    //for(int i = 0; i < 70; i++)
    //    std::cout << RationalNumber::get_prime(i) << " ";
    //std::cout << std::endl;

    rn first;
    rn second(13);
    rn third(15, 3);
    std::cout << first << std::endl;
    std::cout << second<< std::endl;
    std::cout << third<< std::endl;
    first = second;
    first += 3;
    std::cout << first<< std::endl;
    third = rn(2, 5);
    std::cout << third << std::endl;
    third += rn(3, 5);
    std::cout << third<< std::endl;
    return 0;
    
}
*/
