#pragma once

#include <QL/Definitions/Objects/array.hpp>

#include <QL/Definitions/int.hpp>

namespace ql {
    namespace maths {
        Array<float32_t,2> calcMatrix(int32_t x, int32_t y, float32_t angle);
        template<class T> constexpr bool isBit(T v, uint8_t b);
    }
}

#include "maths.inl"