#pragma once

#include "../Arrays/array.hpp"

#include <cstdint>

namespace ql {
    namespace maths {
        Array<float,2> calcMatrix(int32_t x, int32_t y, float angle);
        bool getBit(int64_t var, char bit);
    }
}