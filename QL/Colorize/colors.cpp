#include "colors.hpp"

#include <cstdint>
#include <iostream>

ql::Pixel::Pixel(uint32_t pixel) {
    unsigned char* a_r = (unsigned char*)&pixel;
    unsigned char* a_g = a_r+1;
    unsigned char* a_b = a_r+2;
    unsigned char* a_alpha = a_r+3;

    r = *a_r;
    g = *a_g;
    b = *a_b;
    alpha = *a_alpha;
    
}

bool ql::Pixel::operator==(const ql::Pixel& pix) const {
    return (r == pix.r && g == pix.g && b == pix.b && alpha == pix.alpha);
}

ql::Pixel ql::Pixel::merge(ql::Pixel what) {
    what.alpha = 255 - what.alpha;
    float d = (float)what.alpha / 255;
    
    what.r -= (d*what.r);
    what.g -= (d*what.g);
    what.b -= (d*what.b);

    what.r += (d*r);
    what.g += (d*g);
    what.b += (d*b);

    *this = what;
}