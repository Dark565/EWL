#include <Formats/bmp.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>



void ql::bmp::loadHeaders(FILE* f, struct ql::bmp::Headers* heads) {
    fseek(f,0,SEEK_SET);
    //fread(&heads->bmp_magic,1,ql::bmp::Magics,f);
    //fread(&heads->bmp_header,1,ql::bmp::BMPs,f);
    //fread(&heads->dib_header,1,ql::bmp::DIBs,f);
    fread(heads,1,sizeof(ql::bmp::Headers), f);
}

void ql::bmp::constructHeaders(struct ql::bmp::Headers* heads, uint32_t width, uint32_t height) {
    heads->bmp_magic.signature[0] = 'B';
    heads->bmp_magic.signature[1] = 'M';
    heads->bmp_header.data_offset = 54;
    heads->bmp_header.file_size = width * height * 3 + ql::bmp::FILEs;

    heads->dib_header.compression = ql::bmp::BI_RGB;
    heads->dib_header.colors_used = 0;
    heads->dib_header.bits_per_pixel = 24;
    heads->dib_header.planes = 1;
    heads->dib_header.size = ql::bmp::DIBs;
    heads->dib_header.image_size = 0;
    heads->dib_header.important_colors = 0;
    heads->dib_header.x_pixels_per_meter = 2835;
    heads->dib_header.y_pixels_per_meter = 2835;
    heads->dib_header.width = width;
    heads->dib_header.height = height;
}

void ql::bmp::readImage(FILE* f, ql::bmp::Headers* head, uint8_t* pixels) {
    fseek(f,head->bmp_header.data_offset,SEEK_SET);

    uint32_t px_p_b = head->dib_header.bits_per_pixel/8;
    uint32_t size = head->dib_header.width * head->dib_header.height * px_p_b;

    fread(pixels,size,size,f);

}

void ql::bmp::writeImage(FILE* f, ql::bmp::Headers* heads, const uint8_t* pixels) {
    fseek(f,0,SEEK_SET);

    //fwrite(&heads->bmp_magic,1,ql::bmp::Magics,f);
    //fwrite(&heads->bmp_header,1,ql::bmp::BMPs,f);
    //fwrite(&heads->dib_header,1,ql::bmp::DIBs,f);

    fwrite(heads,1,sizeof(ql::bmp::Headers),f);

    uint32_t bt_p_px = heads->dib_header.bits_per_pixel/8;
    uint32_t size = heads->dib_header.width * heads->dib_header.height * bt_p_px;

    fseek(f,heads->bmp_header.data_offset,SEEK_SET);
    fwrite(pixels, 1, size, f);
}