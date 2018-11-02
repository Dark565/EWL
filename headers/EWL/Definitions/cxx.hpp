#pragma once

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#include <cstdio>

namespace ewl {
    namespace cxx {

        template <class T, class ...Args>
        constexpr void reconstruct(T& object, Args&... args) {
            new (&object) T(args...);
        }

        template <class T>
        constexpr void deconstruct(T* object) {
            delete object;
        }

        template <class T>
        constexpr size_t size(const T& a) {
            return sizeof(a);
        }

        template <class T, class ...Args>
        constexpr size_t size(const T& a, const Args&... args) {
            return size(a) + size(args...);
        }

    }
}