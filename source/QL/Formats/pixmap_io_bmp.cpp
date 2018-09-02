#include <QL/Graphics/pixmap.hpp>
#include <QL/Formats/bmp.hpp>
#include <stdlib.h>

bool ql::Pixmap::loadFromBMP(const char* path) {
    destroy();

    FILE* f = fopen(path,"r");
    if(f) {
        ql::bmp::Headers heads;
        ql::bmp::loadHeaders(f,&heads);

        create(heads.dib_header.width, heads.dib_header.height,ql::Black,heads.dib_header.bits_per_pixel/8);

        ql::bmp::readImage(f,&heads,pixels);

        fclose(f);

        return 1;
    }

    return 0;
}

bool ql::Pixmap::exportToBMP(const char* path) const {
    if(isLegit()) {
        FILE* f = fopen(path,"w");
        if(f) {
            ql::bmp::Headers heads;
            ql::bmp::constructHeaders(&heads,size_x,size_y,bytes_per_pixel);

            ql::bmp::writeImage(f,&heads,pixels);

            fclose(f);
            return 1;
        }
    }

    return 0;
}