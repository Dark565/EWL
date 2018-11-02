#pragma once

#include <EWL/Definitions/int.hpp>

namespace ewl {
    template<class T ,int size> struct Array {
        T x[size];

        template<class... Args>
        constexpr Array(Args... args) : x{args...}
        {}

        constexpr T& operator[](uint32_t i) {
            return x[i];
        }

        constexpr const T& operator[](uint32_t i) const {
            return x[i];
        }
    };
}