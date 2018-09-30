#pragma once

#include <QL/Definitions/int.hpp>

namespace ql {
    template<class T ,int size> struct Array {
        T x[size];

        template<class... Args>
        constexpr Array(Args... args) : x{args...}
        {}

        constexpr T& operator[](uint32_t i) {
            return x[i];
        }

        constexpr const T& operator[](uint32_t i) {
            return x[i];
        }
    };
}