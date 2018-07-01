#pragma once

#include <stdint.h>
#include <QL/Definitions/preprocessor.hpp>

#define QL_PRE_VECTOR(count,...) \
    template <class T> \
    struct vector##count { \
        T __VA_ARGS__; \
    };

#define QL_GET_VECTOR(count) \
    vector##count

namespace ql {

    QL_PRE_VECTOR(2,x,y);
    QL_PRE_VECTOR(3,x,y,z);

    namespace type {

        typedef vector2<int> vec2i;
        typedef vector2<float> vec2f;
        typedef vector2<double> vec2d;

        typedef vector3<int> vec3i;
        typedef vector3<float> vec3f;
        typedef vector3<double> vec3d;


    }
}