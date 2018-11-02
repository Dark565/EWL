#pragma once

#include <EWL/Definitions/int.hpp>

#include <string>

namespace ewl {
    namespace memory {

        /* Exports bytes what are in the range */
        size_t filterByRange(const void*, void*, size_t, const uint8_t*, size_t);

    }
}