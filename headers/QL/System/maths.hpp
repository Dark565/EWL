#pragma once

#include <QL/Definitions/Objects/array.hpp>

#include <cstdint>

namespace ql {
    namespace maths {
        Array<float,2> calcMatrix(int32_t x, int32_t y, float angle);
        template<class T> constexpr bool isBit(T v, uint8_t b);
    }
}

#include "maths.inl"