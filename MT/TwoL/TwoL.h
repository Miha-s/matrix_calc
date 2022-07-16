#ifndef TWOLIST_H
#define TWOLIST_H
/* twolist.h */
// doubly linked list

template <class T>
class TwoL {
    int size;
    struct elem {
        T data;
        elem* prev;
        elem* next;
    };
    elem* first;
    elem* last;
    elem* find_by_index(int pos);
#ifdef TESTING
    friend class testList;
#endif
public:

    TwoL() : size(0), first(0), last(0){}
    TwoL(const T &element);
    TwoL(const TwoL<T> &list);
    ~TwoL();
    
    int get_size();
    void push(const T &element);
    void pushFront(const T &element);
    void pop();
    void popFront();
    void insertA(elem* pos, const T &element); // insert after element
    void insertB(elem* pos, const T &element); // insert before element
    void del(elem* pos);

    void insertA(int pos, const T &element); // insert after position
    void insertB(int pos, const T &element); // insert before position
    void del(int pos);

    void operator=(const TwoL<T> &list);
    void operator+=(const T &element);

    void clear();
// add later
//  void operator+=(const TwoL<T> &list);
//  void clear
    void operator--();
    T& operator[](int pos); 
};

#include "twolist.cpp"


#endif
