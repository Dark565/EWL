#include "../pixmap.hpp"

#include <tiffio.h>

bool ql::Pixmap::loadFromTIFF(const char* path) {
    TIFF* tiff = TIFFOpen(path,"r");
    if(tiff) {
        TIFFGetField(tiff,TIFFTAG_IMAGEWIDTH,&this->size_x);
        TIFFGetField(tiff,TIFFTAG_IMAGELENGTH, &this->size_y);
        int pix_size = this->size_x * this->size_y;

        this->pixels = (uint32_t*)malloc(sizeof(uint32_t) * pix_size);
        if(TIFFReadRGBAImage(tiff,this->size_x, this->size_y, this->pixels, 0)) {
            for(uint32_t x = 0; x < this->size_x; x++) {
                for(uint32_t y = 0; y <= this->size_y/2; y++) {
                    
                    uint32_t tmprgb = pixels[y*this->size_x+x];
                    pixels[y*this->size_x+x] = pixels[(this->size_y-1-y)*this->size_x+x];
                    pixels[(this->size_y-1-y)*this->size_x+x] = tmprgb;
                }
            }

            return 1;
        }
    }
    return 0;
}

bool ql::Pixmap::exportToTIFF(const char* path) const {
    if(isLegit()) {
        TIFF* f = TIFFOpen(path,"w");
        if(f) {
            uint16_t samples = 3;

            TIFFSetField(f,TIFFTAG_IMAGELENGTH,size_y);
            TIFFSetField(f,TIFFTAG_IMAGEWIDTH,size_x);
            TIFFSetField(f,TIFFTAG_SAMPLESPERPIXEL,samples);
            TIFFSetField(f,TIFFTAG_PLANARCONFIG,PLANARCONFIG_CONTIG);
            TIFFSetField(f,TIFFTAG_COMPRESSION, COMPRESSION_LZW);
            TIFFSetField(f,TIFFTAG_BITSPERSAMPLE, 8);
            TIFFSetField(f,TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(f,size_x*samples));

            for(uint32_t y = 0; y < size_y; y++) {
                unsigned char* rgb = (unsigned char*)malloc(samples*size_x);

                for(uint32_t x = 0; x < size_x; x++) {
                    unsigned char* r = (unsigned char*)&pixels[y*size_x+x];
                    unsigned char* g = r+1;
                    unsigned char* b = r+2;

                    rgb[x*samples] = *r;
                    rgb[x*samples+1] = *g;
                    rgb[x*samples+2] = *b;
                }

                if(TIFFWriteScanline(f,rgb,y));
                free(rgb);
            }

            TIFFClose(f);

            return true;

        }
    }
    return false;
}