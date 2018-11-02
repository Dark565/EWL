#include <EWL/System/maths.hpp>

#include <EWL/Definitions/Objects/type_arrays.hpp>

#include <EWL/Definitions/int.hpp>
#include <math.h>

ewl::array2<float> ewl::maths::calcMatrix(ewl::int32_t x, ewl::int32_t y, ewl::float32_t angle) {
    ewl::Array<ewl::float32_t,2> mr;

    mr[0] = ((ewl::float32_t)x * cos(angle) + (ewl::float32_t)y * sin(angle));
    mr[1] = ((ewl::float32_t)x * -sin(angle) + (ewl::float32_t)y * cos(angle));

    return mr;
}