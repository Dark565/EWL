#pragma once

namespace ql {
    /*Force type is container for one variable pointer
    * In copy process, container forcely copies variable from second variable, what means
    * constructor and operator = will never be used, whenever destructor still works */

    template <class T> class force_type {
    private:
        T* ptr;
        void alloc();
        void free();
    public:
        typedef T value_type;

        constexpr operator T() const;
        constexpr T& getValue() const;
        constexpr T** getPtr() const;
        constexpr bool isCreated() const;

        force_type& operator =(const force_type&);
        force_type& operator =(const T&);

        force_type(const force_type&);
        force_type(const T&);

        ~force_type();

        force_type() : ptr(0) 
        {
        };
    };
}

#include "force_type.inl"