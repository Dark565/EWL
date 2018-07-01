#pragma once

#include <stdlib.h>
#include <stdio.h>

#include <cstdio>

namespace ql {
    namespace cxx {


        template <class T, T N>
        struct value {
            enum {
                result = N
            };
        };

        template <class N>
        using number = value<long long, N>; 

        template <class T>
        class has_destructor {


            static int chck(number<empty((void*)T::~T)> {return 0;}
            static char chck( ... ) {return 0;}

        public:

            enum {
                value = (sizeof(chck(0)) == sizeof(int))
            };

        };


        template <class T, class ...Args>
        constexpr void reconstruct(T& object, Args... args) {
            new (&object) T(args...);
        }

        template <class T, class ...Args>
        T* change(T* ptr, uint32_t size, uint32_t after, Args... args) {

        }

    }
}