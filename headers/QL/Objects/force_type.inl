#include "force_type.hpp"
#include <stdlib.h>
#include <string.h>

template <class T>
constexpr T& ql::force_type<T>::getValue() const {
    return *ptr;
}

template <class T>
constexpr ql::force_type<T>::operator T() const {
    return getValue();
}

template <class T>
constexpr bool ql::force_type<T>::isCreated() const {
    return ptr;
}

template <class T>
constexpr T** ql::force_type<T>::getPtr() const {
    return ptr;
}

template <class T>
void ql::force_type<T>::alloc() {
    ptr = (T*)malloc(sizeof(T));
}

template <class T>
void ql::force_type<T>::free() {
    delete ptr;
}

template <class T>
ql::force_type<T>& ql::force_type<T>::operator =(const ql::force_type<T>& second) {
    if(second.isCreated()) {
        *this = *second.ptr;
    }
    return *this;
}

template <class T>
ql::force_type<T>& ql::force_type<T>::operator =(const T& value) {
    if(isCreated()) {
       free();
    }
    alloc();
    memcpy(ptr,&value, sizeof(T));
}

template <class T>
ql::force_type<T>::force_type(const ql::force_type<T>& second) {
    ptr = 0;
    *this = second;
}

template <class T>
ql::force_type<T>::force_type(const T& value) {
    ptr = 0;
    *this = value;
}

template <class T>
ql::force_type<T>::~force_type() {
    if(isCreated()) free();
}