#include <QL/Maths/maths.hpp>

#include <QL/Arrays/array.hpp>
#include <QL/Colorize/colors.hpp>

#include <cstdint>
#include <math.h>

ql::Array<float,2> ql::maths::calcMatrix(int32_t x, int32_t y, float angle) {
    ql::Array<float,2> mr;

    mr.x[0] = ((float)x * cos(angle) + (float)y * sin(angle));
    mr.x[1] = ((float)x * -sin(angle) + (float)y * cos(angle));

    return mr;
}