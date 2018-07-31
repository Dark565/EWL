#include <QL/System/maths.hpp>

#include <QL/Definitions/Objects/type_arrays.hpp>

#include <QL/Definitions/int.hpp>
#include <math.h>

ql::array2<float> ql::maths::calcMatrix(ql::int32_t x, ql::int32_t y, ql::float32_t angle) {
    ql::Array<ql::float32_t,2> mr;

    mr[0] = ((ql::float32_t)x * cos(angle) + (ql::float32_t)y * sin(angle));
    mr[1] = ((ql::float32_t)x * -sin(angle) + (ql::float32_t)y * cos(angle));

    return mr;
}