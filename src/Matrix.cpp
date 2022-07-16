#define FORFOR(I, J)    for(unsigned i = 0; i < I; i++)\
                            for(unsigned j = 0; j < J; j++)

inline int powmin(unsigned i)
{
    return i%2 == 0 ? 1 : -1;
}

inline void checksize(unsigned s1x, unsigned s1y, unsigned s2x, unsigned s2y)
{
    if(s1x != s2x || s1y != s2y)
        throw mt_excep(IS);
}

template <class T>
Matrix<T>::Matrix(unsigned x, unsigned y) : Mx(x), My(y) 
{
    mat = new Vector<T>*[My];
    for(unsigned i = 0; i < My; i++)
        mat[i] = new Vector<T>(Mx);
    square = (Mx == My);
}

template <class T>
Matrix<T>::Matrix(unsigned x, unsigned y, const T& first, ...) : Mx(x), My(y)
{
    mat = new Vector<T>*[My];
    for(unsigned i = 0; i < My; i++)
        mat[i] = new Vector<T>(Mx);
    square = (Mx == My);
    va_list vl;
    va_start(vl, first);
    (*mat[0])[0] = first;
    for(unsigned i = 1; i < Mx; i++)
        (*mat[0])[i] = va_arg(vl, T);
    for(unsigned i = 1; i < My; i++)
        for(unsigned j = 0; j < Mx; j++)
            (*mat[i])[j] = va_arg(vl, T);
    va_end(vl);
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &m) : Mx(m.Mx), My(m.My), square(m.square)
{
    mat = new Vector<T>*[My];
    for(unsigned i = 0; i < My; i++) {
        mat[i] = new Vector<T>(Mx);
        for(unsigned j = 0; j < Mx; j++)
            (*mat[i])[j] = m.get_elem(i, j);
    }
}

template <class T>
Matrix<T>::~Matrix()
{
    for(unsigned i = 0; i < My; i++)
        delete mat[i];
    delete[] mat;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) 
{
    checksize(Mx, My, m.Mx, m.My);
    Matrix<T> tmp(My, Mx);
    FORFOR(My, Mx)
        tmp[i][j] = (*this)[i][j] + m.get_elem(i, j);
    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &m) 
{
    checksize(Mx, My, m.Mx, m.My);
    Matrix<T> tmp(My, Mx);
    FORFOR(My, Mx)
        tmp[i][j] = (*this)[i][j] - m.get_elem(i, j);
    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &m)
{
    if(Mx != m.My)
        throw mt_excep(IS);
    Matrix<T> tmp(m.Mx, My);
    FORFOR(My, m.Mx) {
        tmp[i][j] = 0;
        for(unsigned h = 0; h < Mx; h++) 
            tmp[i][j] += (*this)[i][h]*m.get_elem(h, j);
    }

    return tmp;
}


template <class T>
Vector<T> Matrix<T>::operator*(const Vector<T> &v)
{
    if(Mx != v.gets())
        throw mt_excep(IS);
    Vector<T> tmp(My);
    for(unsigned i = 0; i < My; i++) {
        tmp[i] = 0;
        for(unsigned j = 0; j < Mx; j++)
            tmp[i] += (*this)[i][j] * v.get_elem(j);
    }
    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T &num)
{
    Matrix tmp(Mx, My);
    FORFOR(My, Mx)
        tmp[i][j] = (*this)[i][j] * num;
    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator/(const T &num)
{
    Matrix tmp(Mx, My);
    FORFOR(My, Mx)
        tmp[i][j] = (*this)[i][j] / num;
    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &m) 
{
    if(mat) {
        checksize(Mx, My, m.Mx, m.My);
        FORFOR(My, Mx)
            (*this)[i][j] = m.get_elem(i, j);
    } else {
        Mx = m.Mx;
        My = m.My;
        square = m.square;
        mat = new Vector<T>*[My];
        for(unsigned i = 0; i < My; i++) {
            mat[i] = new Vector<T>(Mx);
            for(unsigned j = 0; j < Mx; j++)
                (*mat[i])[j] = m.get_elem(i, j);
        }
    }

    return *this;
}


template <class T>
bool Matrix<T>::operator==(const Matrix<T> &m) 
{
    checksize(Mx, My, m.Mx, m.My);
    FORFOR(My, Mx)
        if((*this)[i][j] != m.get_elem(i, j))
            return false;
    return true;
}

template <class T>
Matrix<T> Matrix<T>::operator+=(const Matrix<T> &m) 
{
    return *this = *this + m;
}

template <class T>
Matrix<T> Matrix<T>::operator-=(const Matrix<T> &m) 
{
    return *this = *this - m;
}

template <class T>
Matrix<T> Matrix<T>::operator*=(const Matrix<T> &m)
{
    return *this = *this * m;
}

template <class T>
Matrix<T> Matrix<T>::operator*=(const T &num)
{
    return *this = *this * num;
}

template <class T>
Matrix<T> Matrix<T>::operator/=(const T &num)
{
    return *this = *this / num;
}

template <class T>
Matrix<T> Matrix<T>::operator~()
{
    Matrix<T> tmp(My, Mx);
    FORFOR(My, Mx)
        tmp[j][i] = (*this)[i][j];
    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::submatrix(unsigned row, unsigned col) const
{
    if(row > My+1 || col > Mx+1 || row == 0 || col == 0)
        throw mt_excep(IS);
    Matrix<T> tmp(Mx-1, My-1);
    int rowx = 0;
    int colx = 0;
    for(unsigned h = 0; h < My; h++) {
        colx = 0;
        if(h+1 == row) {
            rowx=1;
            continue;
        }
        for(unsigned s = 0; s < Mx; s++) {
            if(s+1 == col) {
                colx = 1;
                continue;
            }
            tmp[h-rowx][s-colx] = get_elem(h, s);
        }
    }
    return tmp;
}

template <class T>
T Matrix<T>::determinant(const Matrix<T> &m)
{
    if(!m.square)
        throw mt_excep(US);
    if(m.Mx == 1)
        return m.get_elem(0,0);
    T det = 0;
    T mult = 1;
    for(unsigned i = 0; i < m.Mx; i++) {
        mult = 1;
        mult *= m.get_elem(0, i)*determinant(m.submatrix(1, i+1))*powmin(i);
        det += mult;
    }
    return det;
}

template <class T>
T Matrix<T>::determinant()
{
    return determinant(*this);
}

template <class T>
Matrix<T> Matrix<T>::operator!()
{
    T det = determinant();
    if(det == 0 || !square)
        throw mt_excep(US);
    Matrix<T> tmp(Mx, My);
    FORFOR(My, Mx) 
        tmp[i][j] = determinant(submatrix(i+1, j+1))*powmin(i+j);
    tmp = ~tmp;
    tmp /= det;
    return tmp;
}

template <class T>
T Matrix<T>::get_elem(unsigned i, unsigned j) const
{
    if(i > My || j > Mx)
        throw mt_excep(II);
    return mat[i]->get_elem(j);
}

template <class T>
Vector<T>& Matrix<T>::operator[](unsigned idx)
{
    if(idx > My)
        throw mt_excep(II);
    return *mat[idx];
}
