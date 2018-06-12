#include <QL/Pixmap/pixmap.hpp>

#include <QL/Colorize/colors.hpp>
#include <QL/Arrays/array.hpp>
#include <QL/Maths/maths.hpp>

/*C/C++ libraries*/

#include <cstdint>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

////

void ql::Pixmap::create(uint32_t a_size_x, uint32_t a_size_y, const Pixel& col, uint32_t bps) {
    destroy();
    deletable = true;

    pixels = (uint8_t*)malloc(sizeof(uint32_t)*a_size_x*a_size_y*bps);
    size_x = a_size_x;
    size_y = a_size_y;

    bytes_per_pixel = bps;
    
    for(uint32_t x = 0; x < a_size_x * a_size_y; x++) {
        memcpy(&pixels[x*bps],&col,bps);
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

ql::Pixmap ql::Pixmap::constructLesser(uint64_t ch, uint32_t ch_count) const {
    ql::Pixmap px;

    if(isLegit()) {

        if(ch != ql::Pixmap::Channels::C_RGBA) {

            uint32_t ch_sz = 0;

            for(uint32_t i = 0; i < 4; i++) {
                if(ql::maths::isBit(ch,i)) ch_sz++;
            }
            uint32_t s = size_x * size_y * ch_sz;
            px.create(size_x,size_y,ql::Black,ch_sz);

            for(uint32_t x = 0; x < size_x*size_y; x++) {
                ql::Pixel px;
                uint8_t* px_c_ptr = (uint8_t*)&px;


                uint32_t curr_c = 0;
                for(uint32_t c = 0; c < ch_sz; c++) {
                    while(!ql::maths::isBit(ch,curr_c)) curr_c++;
                    px_c_ptr[curr_c] = getPixelX(x).getAsCharPtr()[curr_c];
                }
            }


        } else
        px = *this;
    }
    return px;
}

ql::Pixmap ql::Pixmap::constructDecreased(uint32_t ch_count) const {
    ql::Pixmap px;

    if(isLegit()) {
        px.create(size_x, size_y, ql::Black, ch_count);
        for(uint32_t x = 0; x < size_x * size_y; x++) {
            px.setPixelX(x,getPixelXCareful(x));
        }

    }
    return px;

}

bool ql::Pixmap::copy(const ql::Pixmap& from, bool COPY_BPP_VALUE) {
    if(from.isLegit()) {
        destroy();

        size_x = from.size_x;
        size_y = from.size_y;

        pixels = (uint8_t*)malloc(size_x * size_y * bytes_per_pixel);
        if(COPY_BPP_VALUE) bytes_per_pixel = from.bytes_per_pixel;

        for(uint32_t x = 0; x < size_x * size_y; x++) {
            setPixelX(x,from.getPixelX(x));
        }
        
        return 1;
    }
    return 0;
}

bool ql::Pixmap::scale(uint32_t n_x, uint32_t n_y) {
    if(isLegit()) {
        if(n_x != size_x && n_x != size_y) {
            ql::Pixmap n_p;
            n_p.create(n_x, n_y,ql::Black,bytes_per_pixel);

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

                    tp.alpha_compose(from_p);
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
        n.create(n_width, n_height,ql::Black, bytes_per_pixel);
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
        n_p.create(r_w, r_h, emptyColor, bytes_per_pixel);
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

const uint8_t* ql::Pixmap::getPixelPtr() {
    return pixels;
}

uint32_t ql::Pixmap::getWidth() const {
    return size_x;
}

uint32_t ql::Pixmap::getHeight() const {
    return size_y;
}

uint32_t ql::Pixmap::getSize() const {
    return size_x * size_y;
}

bool ql::Pixmap::isLegit() const {
    return pixels;
}

bool ql::Pixmap::isDeletable() const {
    return deletable;
}

uint32_t ql::Pixmap::getBytesPerPixel() const {
    return bytes_per_pixel;
}

bool ql::Pixmap::setGlobalColor(const ql::Pixel& pix, uint8_t color_channel) {
    if(isLegit()) {
        for(uint32_t x = 0; x < size_x * size_y; x++) {
            for(uint32_t i = 0; i<bytes_per_pixel; i++) {
                if(ql::maths::isBit(color_channel,i)) {
                    getPixelX(x).getAsCharPtr()[i] = pix.getAsCharPtr()[i];
                }
            }
        }
        return true;
    }
    return false;
}

bool ql::Pixmap::setPixelX(uint32_t x, const ql::Pixel& col) {
    if(x < size_x * size_y) {
        memcpy(&pixels[x*bytes_per_pixel],&col,bytes_per_pixel);

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

ql::Pixel ql::Pixmap::getPixelXCareful(uint32_t x) const {
    ql::Pixel px = {0,0,0,0};
    if(x < size_x * size_y) {
        memcpy(&px,&pixels[x*bytes_per_pixel],bytes_per_pixel);
    }
    return px;
}

ql::Pixel& ql::Pixmap::getPixelX(uint32_t x) const {
    if(x < size_x * size_y) {
        return *(Pixel*)&pixels[x*bytes_per_pixel];
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

void ql::Pixmap::setNonDeletableFromMemory(uint8_t* ptr, uint32_t x, uint32_t y, uint32_t bpp) {
    destroy();

    deletable = false;
    pixels = ptr;
    bytes_per_pixel = bpp;

    size_x = x;
    size_y = y;
}

void ql::Pixmap::setDeletableFromMemory(uint8_t* ptr, uint32_t x, uint32_t y, uint32_t bpp) {
    destroy();

    deletable = true;
    pixels = ptr;
    bytes_per_pixel = bpp;

    size_x = x;
    size_y = y;
}

ql::Pixmap& ql::Pixmap::operator=(const ql::Pixmap& pix) {
    copy(pix,true);

    return *this;
}

void ql::Pixmap::init() {
    pixels = NULL;
    deletable = false;
    compressor = NULL;
    compressed = NULL;
    bytes_per_pixel = 4;
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
