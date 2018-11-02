#include <EWL/Graphics/pixmap.hpp>
#include <EWL/Formats/bmp.hpp>
#include <stdlib.h>

bool ewl::Pixmap::loadFromBMP(const char* path) {
    destroy();

    FILE* f = fopen(path,"r");
    if(f) {
        ewl::bmp::Headers heads;
        ewl::bmp::loadHeaders(f,&heads);

        create(heads.dib_header.width, heads.dib_header.height,ewl::Black,heads.dib_header.bits_per_pixel/8);

        ewl::bmp::readImage(f,&heads,pixels);

        fclose(f);

        return 1;
    }

    return 0;
}

bool ewl::Pixmap::exportToBMP(const char* path) const {
    if(isLegit()) {
        FILE* f = fopen(path,"w");
        if(f) {
            ewl::bmp::Headers heads;
            ewl::bmp::constructHeaders(&heads,size_x,size_y,bytes_per_pixel);

            ewl::bmp::writeImage(f,&heads,pixels);

            fclose(f);
            return 1;
        }
    }

    return 0;
}