#include "../MT/Exception.h"

Exception::Exception(const char *mes)
{
    message = cpystr(mes);
}

Exception::Exception(const Exception &ex)
{
    message = cpystr(ex.message);
}

Exception::~Exception()
{
    if(message)
        delete[] message;
}

void Exception::set_mes(const char *mes)
{
    message = cpystr(mes);
}

const char* Exception::show()
{
    return message;
}

Exception Exception::operator=(const Exception &ex)
{
    return message = cpystr(ex.message);
}

