/* Exception.h */
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "str.h"

class Exception {
    char *message;
public:
    Exception() : message(0) {}
    Exception(const char *mes);
    Exception(const Exception &ex);

    void set_mes(const char *mes);
    const char* show();

    Exception operator=(const Exception &ex);

    ~Exception();
};

#endif
