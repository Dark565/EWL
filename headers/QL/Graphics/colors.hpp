#pragma once

#include <cstdint>

namespace ql {
    struct Pixel {
        uint8_t r,g,b,alpha;
        Pixel(uint8_t a_r, uint8_t a_g, uint8_t a_b, uint8_t a_alpha = 255) : r(a_r), g(a_g), b(a_b), alpha(a_alpha) {};
        Pixel() = default;
        Pixel(uint32_t pixel);
        bool operator== (const Pixel& pix) const;

        /*Merges color from other pixel with calling pixel including alpha*/

        constexpr uint32_t getAsUint32() const
        {
            return *(uint32_t*)&r;
        }

        constexpr uint8_t* getAsCharPtr() const
        {
            return (uint8_t*)&r;
        }
        
        constexpr _long() 
        {
            return  getAsUint32();
        }

        constexpr uint8_t* getAsCharPtr() const
        {
            return getAsCharPtr();
        }

        void alpha_compose(Pixel what);
        void add_compose(Pixel what);
    };

    static Pixel Black = {0,0,0};
    static Pixel White = {255,255,255};
    static Pixel Red = {255,0,0};
    static Pixel Green = {0,255,0};
    static Pixel Blue = {0,0,255};
    static Pixel Purple = {128,0,128};
    static Pixel Alpha = {0,0,0,0};
    static Pixel Yellow = {255,255,0,0};

    typedef Pixel Color;
}