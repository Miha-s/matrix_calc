#include "../MT/str.h"

unsigned strsize(const char *str)
{
    int s = 0;
    if(str == 0)
        return s;
    while(str[s])
        s++;
    return s;
}

char *cpystr(const char *str, char *str2)
{
    unsigned s = strsize(str);
    char *tmp;
    if(!str2)
        tmp = new char[s+1];
    else
        tmp = str2;
    for(unsigned i = 0; i <= s; i++)
        tmp[i] = str[i];
    return tmp;
}

char *numToStr(long long num, char *to)
{
    char buf[30];
    buf[0] = 0;
    int i = 0;
    if(num < 0) {
        buf[i] = '-';
        num *= -1;
    }
    i++;
    int rem;
    do {
        rem = num%10;
        num /= 10;
        buf[i] = '0' + rem;
        i++;
    } while( num > 0 );

    buf[i] = 0;
    char *b = buf + 1;
    int s = strsize(b);
    for(int i = 0; i < s/2; i++) {
        char tmp = b[i];
        b[i] = b[s-1-i];
        b[s-1-i] = tmp;
    }
    if(buf[0])
        b = buf;
    if(to)
        cpystr(b, to);
    else 
        to = cpystr(b);

    return to ;
}

void strToNum(const char *str, long long &num)
{   
    num = 0; 
    long long minus = 1;
    int i = 0;
    if(str[i] == '-') {
        minus = -1;
        i++;
    }
    while(str[i]) {
        num *= 10;
        num += (str[i] - '0');
        i++;
    }
    num *= minus;
}

