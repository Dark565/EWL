#pragma once


namespace ql {

    template <class T>
    class iterator {
        T* ptr;
    public:
        constexpr T& operator *() const;
        constexpr T* operator ->() const;

        constexpr T& operator ++();

        constexpr iterator& operator =(iterator& itb);
        constexpr iterator& operator =(T* ptr);
        
        constexpr bool operator ==(iterator& itb) const;

        constexpr iterator(iterator& itb);
        constexpr iterator(T* ptr);
    };
}

#include "iterator.inl"