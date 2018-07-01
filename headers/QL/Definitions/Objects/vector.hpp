#pragma once

#include "iterator.hpp"

#include <cstdint>


namespace ql {
    template <class T> class vector {
        T* ptr;
        uint32_t size;
    public:
        typedef ql::iterator<T> iterator;

        vector(T& arg) : vector();

        template <class... Args>
        vector(Args... args) : vector();

        void push_back(T& arg);

        template <class... Args>
        void push_back(T& farg, Args... args);

        void pop_back();

        T& at(uint32_t num);
        void insert(uint32_t pos, vector<T>& vec);
        void insert(uint32_t pos, T& data);

        template <class... Args>
        void insert(uint32_t pos, T& fdata, Args... args);

        iterator begin();
        iterator end();

        inline T& operator[](uint32_t num);

        bool operator = (vector& vecb);
        bool operator ==(vector& vecb);

        constexpr vector() : ptr(NULL) : size(0)
        {}


    }
}

#include "vector.inl"