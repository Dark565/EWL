#include <stdlib.h>
#include <stdio.h>

#include <QL/Definitions/cxx.hpp>

template <class T>
ql::vector<T>::vector(T& arg) {
    push_back(arg);
}

template <class T>
template <class... Args>
ql::vector<T>::vector(Args... args) {
    push_back(args...);
}

template <class T>
void ql::vector<T>::push_back(T& arg) {
    size++;
    ptr = (T*)realloc(ptr, sizeof(T)*size);
    ql::reconstruct(ptr[size-1]);
    ptr[size-1] = arg;
}

template <class T>
template <class... Args>
void ql::vector<T>::push_back(T& farg, Args... args) {
    push_back(farg);
    push_back(args...);
}

template <class T>
void ql::vector<T>::pop_back() {
    if(size > 0) {
        size--;
        delete &ptr[size];
        ptr = re
        
    }
}

