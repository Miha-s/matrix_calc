/* Vector.h */
#ifndef VECTOR_H
#define VECTOR_H
#include <stdarg.h>
#include "excep.h"

template <class T>
class Vector {
    unsigned size;
    T *vec;
public:
    Vector() : vec(0) {}
    Vector(const unsigned s);
    Vector(const unsigned s, const T &first, ...);
    Vector(const Vector<T> &v);
    ~Vector() { delete[] vec; }

    unsigned gets() const { return size; }

    Vector<T> operator+(const Vector<T> &v);
    Vector<T> operator-(const Vector<T> &v);
    Vector<T> operator*(const T &num);
    Vector<T> operator/(const T &num);

    Vector<T> operator=(const Vector<T> &v);
    Vector<T> operator==(const Vector<T> &v);

    Vector<T> operator+=(const Vector<T> &v);
    Vector<T> operator-=(const Vector<T> &v);
    Vector<T> operator*=(const T &num);
    Vector<T> operator/=(const T &num);

    T get_elem(const unsigned idx) const;
    T& operator[](const unsigned idx);
};


class vc_excep : public excep {
protected:
    using excep::Exception::set_mes;
public:
    vc_excep() : excep() {}
    vc_excep(const vc_excep &ex) : excep(ex) {}
    vc_excep(const ex_type t) : excep() { set_mes(t); }
    
    void set_mes(const ex_type t)
    {
        type = t;
        switch(t) {
            case IS:
                set_mes("Vector: Incompatible sizes");
                break;
            case II:
                set_mes("Vector: Incorrect index");
                break;
            default:
                set_mes("Vector: Error");
                break;
        }
    } 

    ~vc_excep() {}
};

#include "../src/Vector.cpp"

#endif
