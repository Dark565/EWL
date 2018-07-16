#include <QL/Graphics/pixmap.hpp>

#include <tiffio.h>

bool ql::Pixmap::loadFromTIFF(const char* path) {
    TIFF* tiff = TIFFOpen(path,"r");
    if(tiff) {
        TIFFGetField(tiff,TIFFTAG_IMAGEWIDTH, &this->size_x);
        TIFFGetField(tiff,TIFFTAG_IMAGELENGTH, &this->size_y);

        this->bytes_per_pixel = 4;
        int pix_size = this->size_x * this->size_y * this->bytes_per_pixel;

        pixels = (uint8_t*)malloc(pix_size);

        if(TIFFReadRGBAImage(tiff,this->size_x, this->size_y, (uint32_t*)this->pixels)) {
            for(uint32_t x = 0; x < this->size_x; x++) {
                for(uint32_t y = 0; y <= this->size_y/2; y++) {
                    
                    ql::Pixel tmprgb = getPixelX(y*this->size_x+x);
                    setPixelX(y*this->size_x+x,getPixelX((this->size_y-1-y)*this->size_x+x));
                    setPixelX((this->size_y-1-y)*this->size_x+x, tmprgb);
                }
            }

            TIFFClose(tiff);
            return 1;
        }
        TIFFClose(tiff);
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

            ql::Pixmap px = constructDecreased(samples);

            for(uint32_t y = 0; y < size_y; y++) {
                TIFFWriteScanline(f,px.pixels + y * size_x,y);
            }

            TIFFClose(f);

            return true;

        }
    }
    return false;
}