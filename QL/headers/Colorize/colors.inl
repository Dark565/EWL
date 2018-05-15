#include "colors.hpp"

inline uint32_t ql::Pixel::getAsUint32() const {
    return *(uint32_t*)&r;
}