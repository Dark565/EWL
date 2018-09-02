#pragma once

#include <QL/Definitions/int.hpp>
#include <QL/Definitions/compiller.hpp>

namespace ql {
    struct Pixel {

        uint8_t r,g,b,alpha;
        Pixel(uint8_t a_r, uint8_t a_g, uint8_t a_b, uint8_t a_alpha = 255) : r(a_r), g(a_g), b(a_b), alpha(a_alpha) {};
        Pixel(uint32_t pixel) : Pixel(*(Pixel*)&pixel) {}
        Pixel() = default;

        constexpr bool operator== (const Pixel& px)
        {
            return *(uint32_t*)this == *(uint32_t*)&px;
        }

        constexpr bool operator== (uint32_t pixel)
        {
            return *this == *(Pixel*)&pixel;
        }

        constexpr Pixel& operator= (uint32_t pixel)
        {
            *this = *(Pixel*)&pixel;
            return *this;
        }

        /*Merges color from other pixel with calling pixel including alpha*/

        constexpr uint32_t* getAsUin32Ptr() const
        {
            return (uint32_t*)&r;
        }

        constexpr uint8_t* getAsCharPtr() const
        {
            return (uint8_t*)&r;
        }
        
        constexpr uint32_t* _long_p() 
        {
            return getAsUin32Ptr();
        }

        constexpr uint8_t* _char_p() const
        {
            return getAsCharPtr();
        }

        constexpr uint8_t& operator[](size_t i) const
        {
            return getAsCharPtr()[i];
        }

        void alpha_compose(Pixel what);
        void add_compose(Pixel what);
    };

    static const Pixel Black = {0,0,0};
    static const Pixel White = {255,255,255};
    static const Pixel Red = {255,0,0};
    static const Pixel Green = {0,255,0};
    static const Pixel Blue = {0,0,255};
    static const Pixel Purple = {255,0,255};
    static const Pixel Alpha = {0,0,0,255};

    typedef Pixel Color;
}