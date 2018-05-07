#include "../pixmap.hpp"

#include <png.h>

bool ql::Pixmap::loadFromPNG(const char* path) {
    FILE* f = fopen(path,"rb");

    unsigned char sig[8];
    fread(sig,1,8,f);
    if(!f) {
        return 0;
    }

    if(!png_sig_cmp(sig,0,8)) {
        return 0;
    }

    png_structp pp = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!pp) {
        return 0;
    }

    png_infop ip = png_create_info_struct(pp);
    if(!ip)  {
        return 0;
    }

    png_init_io(pp,f);
    png_set_sig_bytes(pp,8);

    png_read_info(pp,ip);


    this->size_x = png_get_image_width(pp,ip);
    this->size_y = png_get_image_height(pp,ip);

    png_bytep pxs = (png_bytep)malloc(png_get_rowbytes(pp,ip) * this->size_y);

    png_bytep* rp = (png_bytep*)malloc(sizeof(png_bytep) * this->size_y);
    for(int i = 0; i < this->size_y; i++) {
        rp[i] = &pxs[i*this->size_x];
    }

    png_read_image(pp,rp);

    this->pixels = (uint32_t*)pxs;
    
    fclose(f);
    return 1;

}