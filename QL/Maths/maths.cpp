#include "maths.hpp"

#include "../Arrays/array.hpp"
#include "../Colorize/colors.hpp"

#include <cstdint>
#include <math.h>

ql::Array<float,2> ql::maths::calcMatrix(int32_t x, int32_t y, float angle) {
    ql::Array<float,2> mr;

    mr.x[0] = ((float)x * cos(angle) + (float)y * sin(angle));
    mr.x[1] = ((float)x * -sin(angle) + (float)y * cos(angle));

    return mr;
}

void ql::maths::boxesForBlur(float sigma, float* bx, uint32_t boxes) {
    float vIdeal = sqrt((12.f*sigma*sigma/boxes)+1.f);
    uint32_t vL = floor(vIdeal); if(vL%2 == 0) vL--;
    uint32_t vU = vL+2;

    float vvIdeal = (12.f*sigma*sigma - boxes*vL*vL - 4.f*boxes*vL - 3.f*boxes)/(-4.f*vL - 4.f);
    uint32_t m = round(vvIdeal);

    for(uint32_t i = 0; i < boxes; i++) bx[i] = i < m ? vL : vU;
}

ql::Pixmap ql::maths::calcBlur(ql::Pixmap& from, float radius) {
    ql::Pixmap b; b.create(from.getWidth(),from.getHeight());

    float bxFBlur[3];
    ql::maths::boxesForBlur(radius,bxFBlur,3);

    ql::maths::boxBlur(from,b,(bxFBlur[0]-1)/2.f);
    ql::maths::boxBlur(b,from,(bxFBlur[1]-1)/2.f);
    ql::maths::boxBlur(from,b,(bxFBlur[2]-1)/2.f);

    return b;
}

void ql::maths::boxBlur(ql::Pixmap& from, ql::Pixmap& to, float radius) {
    to = from;
    ql::maths::boxBlurH(to,from,radius);
    ql::maths::boxBlurT(from,to,radius);
}

void ql::maths::boxBlurH(ql::Pixmap& from, ql::Pixmap& to, float radius) {
    float iarr = 1.f / (radius * 2.f + 1.f);
    for(uint32_t i = 0; i < from.getHeight(); i++) {
        uint32_t ti = i*from.getWidth(), li = ti, ri = ti+radius;
        uint32_t fv = from.getPixelX(ti).getAsUint32(), lv = from.getPixelX(ti+from.getWidth()-1).getAsUint32();
        uint32_t val = (radius+1)*fv;
        for(uint32_t j = 0; j < radius; j++) {
            val += from.getPixelX(ti+j).getAsUint32();
        }
        for(uint32_t j = 0; j <= radius; j++) {
            val += from.getPixelX(ri++).getAsUint32() - fv;
            to.setPixelX(ti++,round(iarr*val));
        }
        for(uint32_t j = radius + 1; j < from.getWidth()-radius; j++) {
            val += from.getPixelX(ri++).getAsUint32() - from.getPixelX(li++).getAsUint32();
            to.setPixelX(ti++,round(iarr*val));
        }
        for(uint32_t j = from.getWidth()-radius; j < from.getWidth(); j++) {
            val += lv - from.getPixelX(li++).getAsUint32();
            to.setPixelX(ti++,round(iarr*val));
        }
    }
}

void ql::maths::boxBlurT(ql::Pixmap& from, ql::Pixmap& to, float radius) {
    float iarr = 1.f / (radius * 2.f + 1.f);
    for(uint32_t i = 0; i < from.getWidth(); i++) {
        uint32_t ti = i, li = ti, ri = ti + radius + from.getWidth();
        uint32_t fv = from.getPixelX(ti).getAsUint32(), lv = from.getPixelX(ti+from.getWidth()*(from.getHeight()-1)).getAsUint32();
        uint32_t val = (radius+1)*fv;

        for(uint32_t j = 0; j < radius; j++) {
            val += from.getPixelX(ti+j*from.getWidth()).getAsUint32();
        }
        for(uint32_t j = 0; j <= radius; j++) {
            val += from.getPixelX(ri).getAsUint32() - fv;
            to.setPixelX(ti,round(iarr*val));

            ri+=from.getWidth(); ti+=from.getWidth();
        }
        for(uint32_t j = radius+1; j < from.getHeight()-radius; j++) {
            val += from.getPixelX(ri).getAsUint32() - from.getPixelX(li).getAsUint32();
            to.setPixelX(ti,round(iarr*val));
            li+=from.getWidth(); ri+=from.getWidth();
        }
        for(uint32_t j = from.getHeight()-radius; j < from.getHeight(); j++) {
            val += lv - from.getPixelX(li).getAsUint32();
            to.setPixelX(ti,round(iarr*val));
            li+=from.getWidth(); ti+=from.getWidth();
        }
    }
}

void ql::maths::blurT2(ql::Pixmap& from, ql::Pixmap& to, float radius) {
    const uint32_t w = from.getWidth();
    const uint32_t h = from.getHeight();

    uint32_t rs = ceil(radius * 2.57);
    for(uint32_t i = 0; i < h; i++) {
        for(uint32_t j = 0; j < w; j++) {
            float val = 0, wsum = 0;
            for(uint32_t iy = i - rs; iy<j+rs+1; iy++) {
                for(uint32_t ix = j-rs; ix<j+rs+1; ix++) {
                    uint32_t x = std::min(w-1,std::max(0u,ix));
                    uint32_t y = std::min(h-1,std::max(0u,iy));

                    float dsq = (ix-j)*(ix-j)+(iy-i)*(iy-i);
                    float wght = exp(-dsq / (2.f*radius*radius)) / (M_PI * 2.f * radius * radius);
                    val += wght * from.getPixelX(y*w+x).getAsUint32();
                    wsum += wght; 
                }
                to.setPixelX(i*w+j,round(val/wsum));
            }
        }
    }
}

bool ql::maths::getBit(int64_t var, char bit) {
    while(var) {
        if(!bit) return var%2;
        var/=2;
        bit--;
    }
}