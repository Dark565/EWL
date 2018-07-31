#include <QL/Graphics/pixmap.hpp>

#include <QL/Graphics/colors.hpp>
#include <QL/Definitions/Objects/array.hpp>
#include <QL/System/maths.hpp>

/*C/C++ libraries*/

#include <QL/Definitions/int.hpp>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

////

void ql::Pixmap::create(ql::uint32_t a_size_x, ql::uint32_t a_size_y, const Pixel& col, ql::uint32_t bps) {
    destroy();
    deletable = true;

    pixels = (ql::uint8_t*)malloc(sizeof(ql::uint32_t)*a_size_x*a_size_y*bps);
    size_x = a_size_x;
    size_y = a_size_y;

    bytes_per_pixel = bps;
    
    for(ql::uint32_t x = 0; x < a_size_x * a_size_y; x++) {
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

ql::Pixmap ql::Pixmap::constructLesser(ql::uint64_t ch) const {
    ql::Pixmap px;

    if(isLegit()) {

        if(ch != ql::Pixmap::Channels::C_RGBA) {

            ql::uint32_t ch_sz = 0;

            for(ql::uint32_t i = 0; i < 4; i++) {
                if(ql::maths::isBit(ch,i)) ch_sz++;
            }
            ql::uint32_t s = size_x * size_y * ch_sz;
            px.create(size_x,size_y,ql::Black,ch_sz);

            for(ql::uint32_t x = 0; x < size_x*size_y; x++) {
                ql::Pixel px;
                ql::uint8_t* px_c_ptr = (ql::uint8_t*)&px;


                ql::uint32_t curr_c = 0;
                for(ql::uint32_t c = 0; c < ch_sz; c++) {
                    while(!ql::maths::isBit(ch,curr_c)) curr_c++;
                    px_c_ptr[curr_c] = getPixelX(x).getAsCharPtr()[curr_c];
                }
            }


        } else
        px = *this;
    }
    return px;
}

ql::Pixmap ql::Pixmap::constructDecreased(ql::uint32_t ch_count) const {
    ql::Pixmap px;

    if(isLegit()) {
        px.create(size_x, size_y, ql::Black, ch_count);
        for(ql::uint32_t x = 0; x < size_x * size_y; x++) {
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

        pixels = (ql::uint8_t*)malloc(size_x * size_y * bytes_per_pixel);
        if(COPY_BPP_VALUE) bytes_per_pixel = from.bytes_per_pixel;

        for(ql::uint32_t x = 0; x < size_x * size_y; x++) {
            setPixelX(x,from.getPixelX(x));
        }
        
        return 1;
    }
    return 0;
}

bool ql::Pixmap::scale(ql::uint32_t n_x, ql::uint32_t n_y) {
    if(isLegit()) {
        if(n_x != size_x && n_x != size_y) {
            ql::Pixmap n_p;
            n_p.create(n_x, n_y,ql::Black,bytes_per_pixel);

            ql::float32_t px = (ql::float32_t)size_x / n_x;
            ql::float32_t py = (ql::float32_t)size_y / n_y;

            ql::float32_t f_add_x = 0;
            ql::float32_t f_add_y = 0;

            for(ql::uint32_t xx = 0; xx < n_x; xx++) {
                for(ql::uint32_t yy = 0; yy < n_y; yy++) {
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

bool ql::Pixmap::merge(const Pixmap& ap, ql::uint32_t ax, ql::uint32_t ay, bool EXCLUDE_ALPHA) {
    if(ap.isLegit()) {
        for(ql::uint32_t x = 0; x < ap.size_x; x++) {
            for(ql::uint32_t y = 0; y < ap.size_y; y++) {
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

bool ql::Pixmap::cut(ql::uint32_t from_x, ql::uint32_t from_y, ql::uint32_t to_x, ql::uint32_t to_y) {
    ql::int32_t n_width = to_x - from_x;
    ql::int32_t n_height = to_y - from_y;

    if(isLegit() && n_width >= 0 && n_height >= 0) {
        Pixmap n;
        n.create(n_width, n_height,ql::Black, bytes_per_pixel);
        for(ql::uint32_t x = 0; x < n_width; x++) {
            for(ql::uint32_t y = 0; y < n_height; y++) {
                n.setPixelXY(x,y,getPixelXY(x+from_x,y+from_y));
            }
        }
        *this = n;
    }
    return false;
}

bool ql::Pixmap::rotate(ql::float32_t rad, ql::Pixel emptyColor) {
    if(isLegit()) {

        ql::Array<ql::float32_t,2> coords[4] =  
        {   maths::calcMatrix(0,0,rad),
            maths::calcMatrix(size_x,0,rad),
            maths::calcMatrix(0,size_y,rad),
            maths::calcMatrix(size_x,size_y,rad) };

        ql::int32_t n_w = coords[0][0], n_h = coords[0][1];
        ql::int32_t m_w = coords[0][0], m_h = coords[0][1];

        for(ql::uint32_t i = 1; i < 4; i++) {
            if(coords[i][0] > n_w) n_w = coords[i][0];
            if(coords[i][1] > n_h) n_h = coords[i][1];

            if(coords[i][0] < m_w) m_w = coords[i][0];
            if(coords[i][1] < m_h) m_h = coords[i][1];
        }

        ql::uint32_t r_w = n_w - m_w, r_h = n_h - m_h;

        Pixmap n_p;
        n_p.create(r_w, r_h, emptyColor, bytes_per_pixel);
        for(ql::int32_t x = m_w; x < n_w; x++) {
            for(ql::int32_t y = m_h; y < n_h; y++) {
                
                Array<ql::float32_t,2> m = maths::calcMatrix(x,y,-rad);

                n_p.setPixelXY(x-m_w,y-m_h,getPixelXY(m[0],m[1]));
            }
        }
        *this = n_p;
        return true;
    }
    return false;
}

bool ql::Pixmap::replaceColor(const ql::Pixel& a, const ql::Pixel& b) {
    if(isLegit()) {
        for(ql::uint32_t x = 0; x < size_x * size_y; x++) {
            if(getPixelX(x) == a) setPixelX(x,b);
        }
        return true;
    }
    return false;
}

const ql::uint8_t* ql::Pixmap::getPixelPtr() {
    return pixels;
}

ql::uint32_t ql::Pixmap::getWidth() const {
    return size_x;
}

ql::uint32_t ql::Pixmap::getHeight() const {
    return size_y;
}

ql::uint32_t ql::Pixmap::getSize() const {
    return size_x * size_y;
}

bool ql::Pixmap::isLegit() const {
    return pixels;
}

bool ql::Pixmap::isDeletable() const {
    return deletable;
}

ql::uint32_t ql::Pixmap::getBytesPerPixel() const {
    return bytes_per_pixel;
}

bool ql::Pixmap::setGlobalColor(const ql::Pixel& pix, ql::uint8_t color_channel) {
    if(isLegit()) {
        for(ql::uint32_t x = 0; x < size_x * size_y; x++) {
            for(ql::uint32_t i = 0; i<bytes_per_pixel; i++) {
                if(ql::maths::isBit(color_channel,i)) {
                    getPixelX(x).getAsCharPtr()[i] = pix.getAsCharPtr()[i];
                }
            }
        }
        return true;
    }
    return false;
}

bool ql::Pixmap::setPixelX(ql::uint32_t x, const ql::Pixel& col) {
    if(x < size_x * size_y) {
        memcpy(&pixels[x*bytes_per_pixel],&col,bytes_per_pixel);

        return true;
    }
    return false;
}

bool ql::Pixmap::setPixelXY(ql::uint32_t x, ql::uint32_t y, const ql::Pixel& col) {
    ql::uint32_t index = y * size_x + x;
    return setPixelX(index,col);
}

bool ql::Pixmap::setPixelY(ql::uint32_t y, const ql::Pixel& col) {
    ql::uint32_t index = (y % size_y) * size_x + y / size_y;
    return setPixelX(index,col);
}

ql::Pixel ql::Pixmap::getPixelXCareful(ql::uint32_t x) const {
    ql::Pixel px = {0,0,0,0};
    if(x < size_x * size_y) {
        memcpy(&px,&pixels[x*bytes_per_pixel],bytes_per_pixel);
    }
    return px;
}

ql::Pixel& ql::Pixmap::getPixelX(ql::uint32_t x) const {
    if(x < size_x * size_y) {
        return *(Pixel*)&pixels[x*bytes_per_pixel];
    }
    return *(ql::Pixel*)NULL;
}

ql::Pixel& ql::Pixmap::getPixelY(ql::uint32_t y) const {
    ql::uint32_t index = (y % size_y) * size_x + y / size_y;
    return getPixelX(index);
}

ql::Pixel& ql::Pixmap::getPixelXY(ql::uint32_t x, ql::uint32_t y) const {
    ql::uint32_t index = y * size_x + x;
    return getPixelX(index);
}

bool ql::Pixmap::drawCircle(ql::float32_t radius, int sensitivity, int middle_x, int middle_y, const Pixel& col) {
    for(int i = 0; i < sensitivity; i++) {
        for(int ang_x = 0; ang_x < 360; ang_x++) {
            int x = middle_x + cos(ang_x * (M_PI/180)) * (radius+i);
            int y = middle_y + sin(ang_x * (M_PI/180)) * (radius+i);

            setPixelXY(x,y,col);
        }
    }
}

void ql::Pixmap::setNonDeletableFromMemory(ql::uint8_t* ptr, ql::uint32_t x, ql::uint32_t y, ql::uint32_t bpp) {
    destroy();

    deletable = false;
    pixels = ptr;
    bytes_per_pixel = bpp;

    size_x = x;
    size_y = y;
}

void ql::Pixmap::setDeletableFromMemory(ql::uint8_t* ptr, ql::uint32_t x, ql::uint32_t y, ql::uint32_t bpp) {
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
