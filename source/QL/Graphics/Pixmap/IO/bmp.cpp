#include <QL/Graphics/Pixmap/pixmap.hpp>
#include <QL/Formats/bmp.hpp>
#include <stdlib.h>

bool ql::Pixmap::loadFromBMP(const char* path) {
    destroy();

    FILE* f = fopen(path,"r");
    if(f) {
        ql::bmp::Headers heads;
        ql::bmp::loadHeaders(f,&heads);

        ql::Pixmap pix;
        pix.create(heads.dib_header.width, heads.dib_header.height,ql::Black,3);

        ql::bmp::readImage(f,&heads,(uint8_t*)pix.pixels);
        copy(pix,false);

        fclose(f);

        return 1;
    }

    return 0;
}

bool ql::Pixmap::exportToBMP(const char* path) const {
    if(isLegit()) {
        FILE* f = fopen(path,"w");
        if(f) {
            ql::Pixmap px2 = constructDecreased(3);

            ql::bmp::Headers heads;
            ql::bmp::constructHeaders(&heads,size_x,size_y);

            ql::bmp::writeImage(f,&heads,(const uint8_t*)px2.pixels);

            fclose(f);
            return 1;
        }
    }

    return 0;
}