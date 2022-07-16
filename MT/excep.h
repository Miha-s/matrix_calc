/* Excep.h */
#ifndef EXCEP_H
#define EXCEP_H

#include "Exception.h"

enum ex_type   {  DZ,  // Division by zero
                  NG,  // Negative index
                  IS,  // Incompatible sizes
                  II,  // Incorrect index
                  US,  // Unsuitable size/zero determinant (for !)
                  BS   // Bad string (while converting num)
               };
                  
class excep : public Exception {
protected:
    ex_type type;
public:
    excep() : Exception() {}
    excep(const excep &ex) : Exception(ex), type(ex.type) {}
    // excep(const int t) 
    // You must create this constructor in inherited class
    
    inline void operator=(const excep &ex);
    int what_type() { return type; }

    ~excep() {}
protected: using Exception::set_mes;
};

void excep::operator=(const excep &ex)
{
    Exception::operator=(ex);
    type = ex.type;
}

#endif
