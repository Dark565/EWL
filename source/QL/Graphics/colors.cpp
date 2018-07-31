#include <QL/Graphics/colors.hpp>

#include <QL/Definitions/int.hpp>
#include <iostream>

ql::Pixel::Pixel(ql::uint32_t pixel) {
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

void ql::Pixel::alpha_compose(ql::Pixel what) {
    what.alpha = 255 - what.alpha;
    ql::float32_t d = (ql::float32_t)what.alpha / 255;
    
    what.r -= (d*what.r);
    what.g -= (d*what.g);
    what.b -= (d*what.b);

    what.r += (d*r);
    what.g += (d*g);
    what.b += (d*b);

    *this = what;
}

void ql::Pixel::add_compose(ql::Pixel what) {
    r += what.r;
    g += what.g;
    b += what.b;
}