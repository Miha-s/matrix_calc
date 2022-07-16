
inline void checksize(unsigned s1, unsigned s2)
{
    if(s1 != s2)
        throw vc_excep(IS);
}

template <class T>
Vector<T>::Vector(const unsigned s) 
{
    size = s;
    vec = new T[size];
    for(int i = 0; i < size; i++)
        vec[i] = T(0);
}

template <class T>
Vector<T>::Vector(const unsigned s, const T &first, ...)
{
    size = s;
    vec = new T[size];
    va_list vl;
    va_start(vl, first);
    vec[0] = first;
    for(unsigned i = 1; i < size; i++) 
        vec[i] = va_arg(vl, T);
    va_end(vl);
}
template <class T>
Vector<T>::Vector(const Vector<T> &v)
{
    size = v.size;
    vec = new T[size];
    for(unsigned i = 0; i < size; i++)
        vec[i] = v.vec[i];
}

template <class T>
Vector<T> Vector<T>::operator+(const Vector<T> &v)
{
    checksize(size, v.size);
    Vector<T> tmp(size);
    for(unsigned i = 0; i < size; i++)
        tmp.vec[i] = vec[i] + v.vec[i];
    return tmp;  
}

template <class T>
Vector<T> Vector<T>::operator-(const Vector<T> &v)
{
    checksize(size, v.size);
    Vector<T> tmp(size);
    for(unsigned i = 0; i < size; i++)
        tmp.vec[i] = vec[i] - v.vec[i];
    return tmp;  
}

template <class T>
Vector<T> Vector<T>::operator*(const T &num)
{
    Vector<T> tmp(size);
    for(unsigned i = 0; i < size; i++)
        tmp.vec[i] = vec[i]*num;
    return tmp;  
}

template <class T>
Vector<T> Vector<T>::operator/(const T &num)
{
    Vector<T> tmp(size);
    for(unsigned i = 0; i < size; i++)
        tmp.vec[i] = vec[i]/num;
    return tmp;  
}


template <class T>
Vector<T> Vector<T>::operator=(const Vector<T> &v)
{
    if(vec) 
        checksize(size, v.size);
    else {
        size = v.size;
        vec = new T[size];
    }
    for(unsigned i = 0; i < size; i++)
        vec[i] = v.vec[i];

    return *this;
}


template <class T>
Vector<T> Vector<T>::operator==(const Vector<T> &v)
{
    checksize(size, v.size);
    for(unsigned i = 0; i < size; i++)
        if(vec[i] != v.vec[i])
            return false;
    return true;
}

template <class T>
Vector<T> Vector<T>::operator+=(const Vector<T> &v)
{
    checksize(size, v.size);
    for(unsigned i = 0; i < size; i++)
        vec[i] += v.vec[i];
    return *this;  
}

template <class T>
Vector<T> Vector<T>::operator-=(const Vector<T> &v)
{
    checksize(size, v.size);
    for(unsigned i = 0; i < size; i++)
        vec[i] -= v.vec[i];
    return *this;  
}

template <class T>
Vector<T> Vector<T>::operator*=(const T &num)
{
    for(unsigned i = 0; i < size; i++)
        vec[i] *= num;
    return *this;  
}

template <class T>
Vector<T> Vector<T>::operator/=(const T &num)
{
    for(unsigned i = 0; i < size; i++)
        vec[i] /= num;
    return *this;  
}

template <class T>
T Vector<T>::get_elem(const unsigned idx) const
{
    if(idx > size)
        throw vc_excep(II);
    return vec[idx];
}

template <class T>
T& Vector<T>::operator[](const unsigned idx)
{
    if(idx > size)
        throw vc_excep(II);
    return vec[idx];
}


