template <class T>
TwoL<T>::TwoL(const T &element)
{
    first = 0;
    last = 0;
    size = 0;
    push(element);
}

template <class T>
TwoL<T>::TwoL(const TwoL<T> &list)
{
    first = 0;
    last = 0;
    size = 0;
    (*this) = list;
}

template <class T>
int TwoL<T>::get_size()
{
    return size;
}

template <class T>
void TwoL<T>::push(const T &element)
{
    elem *tmp = new elem;
    if(first == 0) 
        first = tmp; 
    else 
        last->next = tmp;
    tmp->prev = last;
    last = tmp;
    tmp->next = 0;
    tmp->data = element;
    size++;
}

template <class T>
void TwoL<T>::pushFront(const T &element)
{
    elem *tmp = new elem;
    if(!last)
        last = tmp;
    else
        first->prev = tmp;
    tmp->next = first;
    first = tmp;
    tmp->prev = 0;
    tmp->data = element;
    size++;
}

template <class T>
void TwoL<T>::insertA(elem* pos, const T &element)
{
    if(pos == last) {
        push(element);
        return;
    }
    elem* tmp = new elem;
    tmp->data = element;
    pos->next->prev = tmp;
    tmp->next = pos->next;
    pos->next = tmp;
    tmp->prev = pos;
    size++;
}

template <class T>
void TwoL<T>::insertB(elem* pos, const T &element)
{
    if(pos == first) {
        pushFront(element);
        return;
    }
    elem* tmp = new elem;
    tmp->data = element;
    pos->prev->next = tmp;
    tmp->prev = pos->prev;
    tmp->next = pos;
    pos->prev = tmp;
    size++;
}

template <class T>
void TwoL<T>::pop()
{
    if(last == 0)
        return ;
    size--;
    if(last == first) {
        first = 0;
        delete last;
        last = 0;
        return ;
    }
    last = last->prev;
    delete last->next;
    last->next = 0;
}

template <class T>
void TwoL<T>::popFront()
{
    if(last == 0)
        return ;
    size--;
    if(last == first) {
        last = 0;
        delete first;
        first = 0;
        return ;
    }
    first = first->next;
    delete first->prev;
    first->prev = 0;
}

template <class T>
void TwoL<T>::del(elem* pos)
{
    if(pos == last) {
        pop();
        return;
    }
    else if(pos == first) {
        popFront();
        return;
    }
    pos->next->prev = pos->prev;
    pos->prev->next = pos->next;
    delete pos;
    size--;
}

template <class T>
typename TwoL<T>::elem* TwoL<T>::find_by_index(int pos)
{
    elem* tmp;
    if(pos > size/2) {
        tmp = last;
        while(pos < size - 1) {
            tmp = tmp->prev;
            pos++;
        }
    } else {
        tmp = first;
        while(pos) {
            tmp = tmp->next;
            pos--;
        }
    }
    return tmp;
}

template <class T>
void TwoL<T>::insertA(int pos, const T &element)
{
    insertA(find_by_index(pos), element);
}

template <class T>
void TwoL<T>::insertB(int pos, const T &element)
{
   insertB(find_by_index(pos), element); 
}

template <class T>
void TwoL<T>::del(int pos)
{
    del(find_by_index(pos));
}

template <class T>
void TwoL<T>::clear()
{
    while(size) {
        pop();
    }
}

template <class T>
void TwoL<T>::operator+=(const T &element)
{
    push(element);
}

template <class T>
void TwoL<T>::operator--()
{
    pop();
}

template <class T>
T& TwoL<T>::operator[](int pos)
{
    elem* tmp = find_by_index(pos);
    return tmp->data;
}

template <class T>
TwoL<T>::~TwoL<T>()
{
    while(first) {
        last = first;
        first = first->next;
        delete last;
    }
    last = 0;
    size = 0;
}


template <class T>
void TwoL<T>::operator=(const TwoL<T> &list) 
{
    this->~TwoL<T>();
    elem* tmp = list.first;
    while(tmp) {
        push(tmp->data);
        tmp = tmp->next;
    }
}

