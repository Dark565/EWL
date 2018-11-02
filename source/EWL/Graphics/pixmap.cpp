#include <EWL/Graphics/pixmap.hpp>

#include <EWL/Graphics/colors.hpp>
#include <EWL/Definitions/Objects/array.hpp>
#include <EWL/System/maths.hpp>

/*C/C++ libraries*/

#include <EWL/Definitions/int.hpp>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
////

void ewl::Pixmap::create(ewl::uint32_t a_size_x, ewl::uint32_t a_size_y, ewl::uint32_t bps) {
    destroy();
    deletable = true;

    pixels = (ewl::uint8_t*)malloc(a_size_x*a_size_y*bps);
    size_x = a_size_x;
    size_y = a_size_y;

    bytes_per_pixel = bps;
}

bool ewl::Pixmap::fill(const ewl::Pixel& col) {
    if(isLegit()) {
        for(uint32_t i = 0; i < getSize(); i++) {
            memcpy(&getPixelX(i),&col,bytes_per_pixel);
        }
        return true;
    }
    return false;
}

/*void ewl::Pixmap::setCompressor(ewl::Compressor* comp) {
    if(compressor != NULL) delete compressor;
    compressor = comp;
}*/

bool ewl::Pixmap::destroy() {
    if(pixels && deletable) {
        free(pixels);
        pixels = NULL;
        return true;
    }
    return false;
}

ewl::Pixmap ewl::Pixmap::constructLesser(ewl::uint64_t ch) const {
    ewl::Pixmap px;

    if(isLegit()) {

        if(ch != ewl::Pixmap::Channels::C_RGBA) {

            ewl::uint32_t ch_sz = 0;

            for(ewl::uint32_t i = 0; i < 4; i++) {
                if(ewl::maths::isBit(ch,i)) ch_sz++;
            }
            ewl::uint32_t s = size_x * size_y * ch_sz;
            px.create(size_x,size_y,ch_sz);

            for(ewl::uint32_t x = 0; x < size_x*size_y; x++) {
                ewl::Pixel px;
                ewl::uint8_t* px_c_ptr = (ewl::uint8_t*)&px;


                ewl::uint32_t curr_c = 0;
                for(ewl::uint32_t c = 0; c < ch_sz; c++) {
                    while(!ewl::maths::isBit(ch,curr_c)) curr_c++;
                    px_c_ptr[curr_c] = getPixelX(x)[curr_c];
                }
            }


        } else
        px = *this;
    }
    return px;
}

ewl::Pixmap ewl::Pixmap::constructDecreased(ewl::uint32_t ch_count) const {
    ewl::Pixmap px;

    if(isLegit()) {
        px.create(size_x, size_y, ch_count);
        for(ewl::uint32_t x = 0; x < size_x * size_y; x++) {
            px.setPixelX(x,getPixelXSafely(x));
        }

    }
    return px;
}

/*ewl::Pixmap ewl::Pixmap::reconstructBySize(ewl::uint32_t bpp, ewl::uint32_t channels, ewl::int32_t max_bytes_to_set, ewl::int32_t ch_otr) {
    ewl::Pixmap px;
    if(isLegit()) {
        uint32_t curr_bits_pp = bytes_per_pixel * 8, new_bits_pp = bpp * 8;

        px.create(size_x,size_y,bpp);



    }
    return px;
}*/

bool ewl::Pixmap::copy(const ewl::Pixmap& from, bool COPY_BPP_VALUE) {
    if(from.isLegit()) {
        destroy();

        size_x = from.size_x;
        size_y = from.size_y;

        pixels = (ewl::uint8_t*)malloc(size_x * size_y * bytes_per_pixel);
        if(COPY_BPP_VALUE) bytes_per_pixel = from.bytes_per_pixel;

        for(ewl::uint32_t x = 0; x < size_x * size_y; x++) {
            setPixelX(x,from.getPixelX(x));
        }
        
        return 1;
    }
    return 0;
}

bool ewl::Pixmap::scale(ewl::uint32_t n_x, ewl::uint32_t n_y) {
    if(isLegit()) {
        if(n_x != size_x && n_x != size_y) {
            ewl::Pixmap n_p;
            n_p.create(n_x, n_y, bytes_per_pixel);

            ewl::float32_t px = (ewl::float32_t)size_x / n_x;
            ewl::float32_t py = (ewl::float32_t)size_y / n_y;

            ewl::float32_t f_add_x = 0;
            ewl::float32_t f_add_y = 0;

            for(ewl::uint32_t xx = 0; xx < n_x; xx++) {
                for(ewl::uint32_t yy = 0; yy < n_y; yy++) {
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

bool ewl::Pixmap::merge(const Pixmap& ap, ewl::uint32_t ax, ewl::uint32_t ay, bool EXCLUDE_ALPHA) {
    if(ap.isLegit()) {
        for(ewl::uint32_t x = 0; x < ap.size_x; x++) {
            for(ewl::uint32_t y = 0; y < ap.size_y; y++) {
                ewl::Pixel from_p = ap.getPixelXY(x,y);
                if(!EXCLUDE_ALPHA) {
                    ewl::Pixel tp = getPixelXY(x+ax,y+ay);

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

bool ewl::Pixmap::cut(ewl::uint32_t from_x, ewl::uint32_t from_y, ewl::uint32_t to_x, ewl::uint32_t to_y) {
    ewl::int32_t n_width = to_x - from_x;
    ewl::int32_t n_height = to_y - from_y;

    if(isLegit() && n_width >= 0 && n_height >= 0) {
        Pixmap n;
        n.create(n_width, n_height, bytes_per_pixel);
        for(ewl::uint32_t x = 0; x < n_width; x++) {
            for(ewl::uint32_t y = 0; y < n_height; y++) {
                n.setPixelXY(x,y,getPixelXY(x+from_x,y+from_y));
            }
        }
        *this = n;
    }
    return false;
}

bool ewl::Pixmap::rotate(ewl::float32_t rad, ewl::Pixel emptyColor) {
    if(isLegit()) {

        ewl::Array<ewl::float32_t,2> coords[4] =  
        {   maths::calcMatrix(0,0,rad),
            maths::calcMatrix(size_x,0,rad),
            maths::calcMatrix(0,size_y,rad),
            maths::calcMatrix(size_x,size_y,rad) };

        ewl::int32_t n_w = coords[0][0], n_h = coords[0][1];
        ewl::int32_t m_w = coords[0][0], m_h = coords[0][1];

        for(ewl::uint32_t i = 1; i < 4; i++) {
            if(coords[i][0] > n_w) n_w = coords[i][0];
            if(coords[i][1] > n_h) n_h = coords[i][1];

            if(coords[i][0] < m_w) m_w = coords[i][0];
            if(coords[i][1] < m_h) m_h = coords[i][1];
        }

        ewl::uint32_t r_w = n_w - m_w, r_h = n_h - m_h;

        Pixmap n_p;
        n_p.create(r_w, r_h, bytes_per_pixel);
        for(ewl::int32_t x = m_w; x < n_w; x++) {
            for(ewl::int32_t y = m_h; y < n_h; y++) {
                
                Array<ewl::float32_t,2> m = maths::calcMatrix(x,y,-rad);

                n_p.setPixelXY(x-m_w,y-m_h,getPixelXY(m[0],m[1]));
            }
        }
        *this = n_p;
        return true;
    }
    return false;
}

bool ewl::Pixmap::replaceColor(const ewl::Pixel& a, const ewl::Pixel& b) {
    if(isLegit()) {
        for(ewl::uint32_t x = 0; x < size_x * size_y; x++) {
            if(getPixelX(x) == a) setPixelX(x,b);
        }
        return true;
    }
    return false;
}

const ewl::uint8_t* ewl::Pixmap::getPixelPtr() {
    return pixels;
}

ewl::uint32_t ewl::Pixmap::getWidth() const {
    return size_x;
}

ewl::uint32_t ewl::Pixmap::getHeight() const {
    return size_y;
}

ewl::uint32_t ewl::Pixmap::getSize() const {
    return size_x * size_y;
}

bool ewl::Pixmap::isLegit() const {
    return pixels;
}

bool ewl::Pixmap::isDeletable() const {
    return deletable;
}

ewl::uint32_t ewl::Pixmap::getBytesPerPixel() const {
    return bytes_per_pixel;
}

bool ewl::Pixmap::setGlobalColor(const ewl::Pixel& pix, ewl::uint8_t color_channel) {
    if(isLegit()) {
        for(ewl::uint32_t x = 0; x < size_x * size_y; x++) {
            for(ewl::uint32_t i = 0; i<bytes_per_pixel; i++) {
                if(ewl::maths::isBit(color_channel,i)) {
                    getPixelX(x).getAsCharPtr()[i] = pix.getAsCharPtr()[i];
                }
            }
        }
        return true;
    }
    return false;
}

bool ewl::Pixmap::setPixelX(ewl::uint32_t x, const ewl::Pixel& col) {
    if(x < size_x * size_y) {
        memcpy(&pixels[x*bytes_per_pixel],&col,bytes_per_pixel);

        return true;
    }
    return false;
}

bool ewl::Pixmap::setPixelXY(ewl::uint32_t x, ewl::uint32_t y, const ewl::Pixel& col) {
    ewl::uint32_t index = y * size_x + x;
    return setPixelX(index,col);
}

bool ewl::Pixmap::setPixelY(ewl::uint32_t y, const ewl::Pixel& col) {
    ewl::uint32_t index = (y % size_y) * size_x + y / size_y;
    return setPixelX(index,col);
}

ewl::Pixel ewl::Pixmap::getPixelXSafely(ewl::uint32_t x) const {
    ewl::Pixel px = {0,0,0,0};
    if(x < size_x * size_y) {
        memcpy(&px,&pixels[x*bytes_per_pixel],bytes_per_pixel);
    }
    return px;
}

ewl::Pixel& ewl::Pixmap::getPixelX(ewl::uint32_t x) const {
    if(x < size_x * size_y) {
        return *(Pixel*)&pixels[x*bytes_per_pixel];
    }
    return *(ewl::Pixel*)NULL;
}

ewl::Pixel& ewl::Pixmap::getPixelY(ewl::uint32_t y) const {
    ewl::uint32_t index = (y % size_y) * size_x + y / size_y;
    return getPixelX(index);
}

ewl::Pixel& ewl::Pixmap::getPixelXY(ewl::uint32_t x, ewl::uint32_t y) const {
    ewl::uint32_t index = y * size_x + x;
    return getPixelX(index);
}

void ewl::Pixmap::drawCircle(ewl::float32_t radius, int sensitivity, int middle_x, int middle_y, const Pixel& col) {
    for(int i = 0; i < sensitivity; i++) {
        for(float ang_x = 0; ang_x < M_PI*2; ang_x += (M_PI/180)) {
            int x = middle_x + cos(ang_x * (radius+i));
            int y = middle_y + sin(ang_x * (radius+i));

            setPixelXY(x,y,col);
        }
    }
}

void ewl::Pixmap::setNonDeletableFromMemory(ewl::uint8_t* ptr, ewl::uint32_t x, ewl::uint32_t y, ewl::uint32_t bpp) {
    destroy();

    deletable = false;
    pixels = ptr;
    bytes_per_pixel = bpp;

    size_x = x;
    size_y = y;
}

void ewl::Pixmap::setDeletableFromMemory(ewl::uint8_t* ptr, ewl::uint32_t x, ewl::uint32_t y, ewl::uint32_t bpp) {
    destroy();

    deletable = true;
    pixels = ptr;
    bytes_per_pixel = bpp;

    size_x = x;
    size_y = y;
}

ewl::Pixmap& ewl::Pixmap::operator=(const ewl::Pixmap& pix) {
    copy(pix,true);

    return *this;
}

void ewl::Pixmap::init() {
    pixels = NULL;
    deletable = false;
    /*compressor = NULL;
    compressed = NULL;*/
    bytes_per_pixel = 4;
}

ewl::Pixmap::Pixmap() {
    init();
}

ewl::Pixmap::Pixmap(const ewl::Pixmap& pix) {
    init();

    *this = pix;
}

ewl::Pixmap::~Pixmap() {
    destroy();
}
