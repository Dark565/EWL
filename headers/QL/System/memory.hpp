#pragma once

#include <QL/Definitions/int.hpp>

#include <string>

namespace ql {
    namespace memory {

        /* Exports bytes what are in the range */
        size_t filterForRange(const void*, void*, size_t, const uint8_t*, size_t);

    }
}