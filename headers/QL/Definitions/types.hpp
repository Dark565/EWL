#pragma once

#include <stdint.h>

namespace ql {

    template <class T> struct vector2 {
        T x,y;

        constexpr vector2(T _x, T _y) : x(_x), y(_y)
        {
        }
    };

    template <class T> struct vector3 {
        T x,y,z;

        constexpr vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
        {
        }
    };

    template <class T> struct vector4 {
        T x,y,z,w;

        constexpr vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w)
        {
        }
    };

    namespace type {

        using ql::vector2;
        using ql::vector3;
        using ql::vector4;

        typedef vector2<int8_t> vec2c;
        typedef vector2<int16_t> vec2s;
        typedef vector2<int32_t> vec2i;
        typedef vector2<int64_t> vec2ii;
        typedef vector2<float> vec2f;
        typedef vector2<double> vec2d;

        typedef vector3<int8_t> vec3c;
        typedef vector3<int16_t> vec3s;
        typedef vector3<int32_t> vec3i;
        typedef vector3<int64_t> vec3ii;
        typedef vector3<float> vec3f;
        typedef vector3<double> vec3d;

        typedef vector4<int8_t> vec4c;
        typedef vector4<int16_t> vec4s;
        typedef vector4<int32_t> vec4i;
        typedef vector4<int64_t> vec4ii;
        typedef vector4<float> vec4f;
        typedef vector4<double> vec4d;

        typedef vector2<uint8_t> vec2uc;
        typedef vector2<uint16_t> vec2us;
        typedef vector2<uint32_t> vec2ui;
        typedef vector2<uint64_t> vec2uii;

        typedef vector3<uint8_t> vec3uc;
        typedef vector3<uint16_t> vec3us;
        typedef vector3<uint32_t> vec3ui;
        typedef vector3<uint64_t> vec3uii;

        typedef vector4<uint8_t> vec4uc;
        typedef vector4<uint16_t> vec4us;
        typedef vector4<uint32_t> vec4ui;
        typedef vector4<uint64_t> vec4uii;
    }
}