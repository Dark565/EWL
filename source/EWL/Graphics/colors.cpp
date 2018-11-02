#include <EWL/Graphics/colors.hpp>

#include <EWL/Definitions/int.hpp>
#include <iostream>

void ewl::Pixel::alpha_compose(ewl::Pixel what) {
    what.alpha = 255 - what.alpha;
    ewl::float32_t d = (ewl::float32_t)what.alpha / 255;

    what.r -= (d*what.r);
    what.g -= (d*what.g);
    what.b -= (d*what.b);

    what.r += (d*r);
    what.g += (d*g);
    what.b += (d*b);

    *this = what;
}

void ewl::Pixel::add_compose(ewl::Pixel what) {
    r += what.r;
    g += what.g;
    b += what.b;
}
