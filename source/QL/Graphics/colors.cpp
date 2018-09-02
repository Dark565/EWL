#include <QL/Graphics/colors.hpp>

#include <QL/Definitions/int.hpp>
#include <iostream>

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