#pragma once

#include "array.hpp"

#include <stdint.h>


namespace ql {

    template<class T>
    using array2    = Array<T,2>;

    template<class T>
    using array3    = Array<T,3>;

    using array2ui  = array2<uint32_t>;
    using array2i   = array2<int32_t>;
    using array2f   = array2<float>;
    using array2d   = array2<double>;

    using array3ui  = array3<uint32_t>;
    using array3i   = array3<int32_t>;
    using array3f   = array3<float>;
    using array3d   = array3<double>;

}