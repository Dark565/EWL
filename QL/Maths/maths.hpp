#pragma once

#include "../Arrays/array.hpp"
#include "../Pixmap/pixmap.hpp"

#include <cstdint>

namespace ql {
    namespace maths {
        Array<float,2> calcMatrix(int32_t x, int32_t y, float angle);

        ql::Pixmap calcBlur(Pixmap& from, float radius);
        void boxesForBlur(float sigma, float* bx, uint32_t boxes);
        void boxBlur(Pixmap& from, Pixmap& to, float radius);
        void boxBlurH(Pixmap& from, Pixmap& to, float radius);
        void boxBlurT(Pixmap& from, Pixmap& to, float radius);
        void blurT2(Pixmap& from, Pixmap& to, float radius);
        
        bool getBit(int64_t var, char bit);
    }
}