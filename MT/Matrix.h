/* Matrix.h */
#ifndef MATRIX_H
#define MATRIX_H

#include "excep.h"
#include <stdarg.h>
#include "Vector.h"

template<class T>
class Matrix {
    unsigned Mx;
    unsigned My;
    bool square;

    // In future add rows swap
    Vector<T> **mat;
public:
    Matrix() : mat(0) {}
    Matrix(unsigned x, unsigned y);
    Matrix(unsigned x, unsigned y, const T& first, ...);
    Matrix(const Matrix<T> &m);
    ~Matrix();

    unsigned getx() { return Mx; }
    unsigned gety() { return My; }

    Matrix<T> operator+(const Matrix<T> &m);
    Matrix<T> operator-(const Matrix<T> &m);
    Matrix<T> operator*(const Matrix<T> &m);
    Vector<T> operator*(const Vector<T> &v);
    Matrix<T> operator*(const T &num);
    Matrix<T> operator/(const T &num);

    Matrix<T> operator=(const Matrix<T> &m);
    bool operator==(const Matrix<T> &m);

    Matrix<T> operator+=(const Matrix<T> &m);
    Matrix<T> operator-=(const Matrix<T> &m);
    Matrix<T> operator*=(const Matrix<T> &m);
    Matrix<T> operator*=(const T &num);
    Matrix<T> operator/=(const T &num);

    Matrix<T> operator~(); // transposition
    Matrix<T> operator!(); // inverse matrix
    
    T get_elem(unsigned i, unsigned j) const;
    Vector<T>& operator[](unsigned idx);

    Matrix<T> submatrix(unsigned row, unsigned col) const;
    T determinant();
    static T determinant(const Matrix<T> &m);
};
/*
enum mt_ex_type  { IS,  //Incompatible sizes
                   US,  //Unsuitable size/unsuitable determinant (for !)
                   II   //Incorrect index
                 };
*/

class mt_excep : public excep {
protected: 
    using excep::Exception::set_mes;
public:
    mt_excep() : excep() {}
    mt_excep(const mt_excep &ex) : excep(ex) {}
    mt_excep(const ex_type t) : excep() { set_mes(t); }
    
    void set_mes(const ex_type t)
    {
        type = t;
        switch(t) {
            case IS:
                set_mes("Matrix: Incompatible sizes");
                break;
            case US:
                set_mes("Matrix: Unsuitable size/zero determinant (for !)");
                break;
            case II:
                set_mes("Matrix: Incorrect index");
                break;
            default:
                set_mes("Matrix: Error");
                break;
        }
    }

    ~mt_excep() {}
};

#include "../src/Matrix.cpp"
#endif
