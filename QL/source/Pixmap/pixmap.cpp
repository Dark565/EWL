#include <Pixmap/pixmap.hpp>

#include <Colorize/colors.hpp>
#include <Arrays/array.hpp>
#include <Maths/maths.hpp>

/*C/C++ libraries*/

#include <cstdint>
#include <iostream>
#include <math.h>

/*Image libraries*/

#include <png.h>
#include <tiffio.h>
#include <jpeglib.h>

////

void ql::Pixmap::create(uint32_t a_size_x, uint32_t a_size_y, const Pixel& col) {
    destroy();
    deletable = true;

    pixels = (uint32_t*)malloc(sizeof(uint32_t)*a_size_x*a_size_y);
    size_x = a_size_x;
    size_y = a_size_y;
    
    for(uint32_t x = 0; x < a_size_x * a_size_y; x++) {
        pixels[x] = *(uint32_t*)&col;
    }
}

void ql::Pixmap::setCompressor(ql::Compressor* comp) {
    if(compressor != NULL) delete compressor;
    compressor = comp;
}

bool ql::Pixmap::destroy() {
    if(pixels && deletable) {
        free(pixels);
        pixels = NULL;
        return true;
    }
    return false;
}

bool ql::Pixmap::scale(uint32_t n_x, uint32_t n_y) {
    if(isLegit()) {
        if(n_x != size_x && n_x != size_y) {
            ql::Pixmap n_p;
            n_p.create(n_x, n_y);

            float px = (float)size_x / n_x;
            float py = (float)size_y / n_y;

            float f_add_x = 0;
            float f_add_y = 0;

            for(uint32_t xx = 0; xx < n_x; xx++) {
                for(uint32_t yy = 0; yy < n_y; yy++) {
                    n_p.setPixelXY(xx,yy,getPixelXY(f_add_x, f_add_y));
                    f_add_y += py;
                }
                f_add_x += px;
                f_add_y = 0;
            }

            
            *this = n_p;
        }
        return true;
    }
    return false;
}

bool ql::Pixmap::merge(const Pixmap& ap, uint32_t ax, uint32_t ay, bool EXCLUDE_ALPHA) {
    if(ap.isLegit()) {
        for(uint32_t x = 0; x < ap.size_x; x++) {
            for(uint32_t y = 0; y < ap.size_y; y++) {
                ql::Pixel from_p = ap.getPixelXY(x,y);
                if(!EXCLUDE_ALPHA) {
                    ql::Pixel tp = getPixelXY(x+ax,y+ay);

                    tp.merge(from_p);
                    from_p = tp;
                }
                setPixelXY(x+ax, y+ay, from_p);
            }
        }
        return true;
    }
    return false;
}

bool ql::Pixmap::cut(uint32_t from_x, uint32_t from_y, uint32_t to_x, uint32_t to_y) {
    int32_t n_width = to_x - from_x;
    int32_t n_height = to_y - from_y;

    if(isLegit() && n_width >= 0 && n_height >= 0) {
        Pixmap n;
        n.create(n_width, n_height);
        for(uint32_t x = 0; x < n_width; x++) {
            for(uint32_t y = 0; y < n_height; y++) {
                n.setPixelXY(x,y,getPixelXY(x+from_x,y+from_y));
            }
        }
        *this = n;
    }
    return false;
}

bool ql::Pixmap::rotate(float rad, ql::Pixel emptyColor) {
    if(isLegit()) {

        ql::Array<float,2> coords[4] =  
        {   ql::maths::calcMatrix(0,0,rad),
            ql::maths::calcMatrix(size_x,0,rad),
            ql::maths::calcMatrix(0,size_y,rad),
            ql::maths::calcMatrix(size_x,size_y,rad) };

        int32_t n_w = coords[0].x[0], n_h = coords[0].x[1];
        int32_t m_w = coords[0].x[0], m_h = coords[0].x[1];

        for(uint32_t i = 1; i < 4; i++) {
            if(coords[i].x[0] > n_w) n_w = coords[i].x[0];
            if(coords[i].x[1] > n_h) n_h = coords[i].x[1];

            if(coords[i].x[0] < m_w) m_w = coords[i].x[0];
            if(coords[i].x[1] < m_h) m_h = coords[i].x[1];
        }

        uint32_t r_w = n_w - m_w, r_h = n_h - m_h;

        ql::Pixmap n_p;
        n_p.create(r_w, r_h, emptyColor);
        for(int32_t x = m_w; x < n_w; x++) {
            for(int32_t y = m_h; y < n_h; y++) {
                
                Array<float,2> m = ql::maths::calcMatrix(x,y,-rad);

                n_p.setPixelXY(x-m_w,y-m_h,getPixelXY(m.x[0],m.x[1]));
            }
        }
        *this = n_p;
        return true;
    }
    return false;
}

bool ql::Pixmap::replaceColor(const ql::Pixel& a, const ql::Pixel& b) {
    if(isLegit()) {
        for(uint32_t x = 0; x < size_x * size_y; x++) {
            if(getPixelX(x) == a) setPixelX(x,b);
        }
        return true;
    }
    return false;
}

const uint32_t* ql::Pixmap::getPixelPtr() {
    return pixels;
}

uint32_t ql::Pixmap::getWidth() const {
    return size_x;
}

uint32_t ql::Pixmap::getHeight() const {
    return size_y;
}

bool ql::Pixmap::isLegit() const {
    return pixels;
}

bool ql::Pixmap::isDeletable() const {
    return deletable;
}

bool ql::Pixmap::setGlobalColor(const ql::Pixel& pix, uint8_t color_channel) {
    if(isLegit()) {
        for(uint32_t x = 0; x < size_x * size_y; x++) {
            if(ql::maths::getBit(color_channel,0)) {
                getPixelX(x).r = pix.r;
            }
            if(ql::maths::getBit(color_channel,1)) {
                getPixelX(x).g = pix.g;
            }
            if(ql::maths::getBit(color_channel,2)) {
                getPixelX(x).b = pix.b;
            }
            if(ql::maths::getBit(color_channel,3)) {
                getPixelX(x).alpha = pix.alpha;
            }
        }
        return true;
    }
    return false;
}

bool ql::Pixmap::setPixelX(uint32_t x, const ql::Pixel& col) {
    if(x < size_x * size_y) {
        unsigned char* p_r = (unsigned char*)&pixels[x];
        unsigned char* p_g = p_r+1;
        unsigned char* p_b = p_r+2;
        unsigned char* p_a = p_r+3;

        *p_r = col.r;
        *p_g = col.g;
        *p_b = col.b;
        *p_a = col.alpha;

        return true;
    }
    return false;
}

bool ql::Pixmap::setPixelXY(uint32_t x, uint32_t y, const ql::Pixel& col) {
    uint32_t index = y * size_x + x;
    return setPixelX(index,col);
}

bool ql::Pixmap::setPixelY(uint32_t y, const ql::Pixel& col) {
    uint32_t index = (y % size_y) * size_x + y / size_y;
    return setPixelX(index,col);
}

ql::Pixel& ql::Pixmap::getPixelX(uint32_t x) const {
    if(x < size_x * size_y) {
        return *(Pixel*)&pixels[x];
    }
    return *(ql::Pixel*)NULL;
}

ql::Pixel& ql::Pixmap::getPixelY(uint32_t y) const {
    uint32_t index = (y % size_y) * size_x + y / size_y;
    return getPixelX(index);
}

ql::Pixel& ql::Pixmap::getPixelXY(uint32_t x, uint32_t y) const {
    uint32_t index = y * size_x + x;
    return getPixelX(index);
}

bool ql::Pixmap::drawCircle(float radius, int sensitivity, int middle_x, int middle_y, const Pixel& col) {
    for(int i = 0; i < sensitivity; i++) {
        for(int ang_x = 0; ang_x < 360; ang_x++) {
            int x = middle_x + cos(ang_x * (M_PI/180)) * (radius+i);
            int y = middle_y + sin(ang_x * (M_PI/180)) * (radius+i);

            setPixelXY(x,y,col);
        }
    }
}

void ql::Pixmap::setNonDeletableFromMemory(uint32_t* ptr, uint32_t x, uint32_t y) {
    destroy();

    deletable = false;
    pixels = ptr;

    size_x = x;
    size_y = y;
}

void ql::Pixmap::setDeletableFromMemory(uint32_t* ptr, uint32_t x, uint32_t y) {
    destroy();

    deletable = true;
    pixels = ptr;

    size_x = x;
    size_y = y;
}

ql::Pixmap& ql::Pixmap::operator=(const ql::Pixmap& pix) {
    destroy();
    if(pix.isLegit()) {
        pixels = (uint32_t*)malloc(sizeof(uint32_t)*pix.size_x*pix.size_y);
        memcpy(pixels,pix.pixels,sizeof(uint32_t)*pix.size_x*pix.size_y);

        size_x = pix.size_x;
        size_y = pix.size_y;
    }

    return *this;
}

void ql::Pixmap::init() {
    pixels = NULL;
    deletable = false;
    compressor = NULL;
    compressed = NULL;
}

ql::Pixmap::Pixmap() {
    init();
}

ql::Pixmap::Pixmap(const ql::Pixmap& pix) {
    init();

    *this = pix;
}

ql::Pixmap::~Pixmap() {
    destroy();
}
