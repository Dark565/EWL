#include "colors.hpp"


inline uint32_t ql::Pixel::getAsUint32() const {
    return *(uint32_t*)&r;
}

inline uint8_t* ql::Pixel::getAsCharPtr() const {
    return (uint8_t*)&r;
}