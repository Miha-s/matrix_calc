/* str.h */
#ifndef STR_H
#define STR_H

unsigned strsize(const char *str);

char * cpystr(const char *str, char *str2 = 0);

char * numToStr(long long num, char *b = 0);

void strToNum(const char *str, long long &num);
#endif
