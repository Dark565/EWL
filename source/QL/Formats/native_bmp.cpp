#include <QL/Formats/bmp.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>



void ql::bmp::loadHeaders(FILE* f, struct ql::bmp::Headers* heads) {
    fseek(f,0,SEEK_SET);
    fread(heads,1,ql::bmp::FILEs,f);
}

void ql::bmp::constructHeaders(struct ql::bmp::Headers* heads, ql::uint32_t width, ql::uint32_t height, ql::uint32_t bps) {
    heads->bmp_magic.signature[0] = 'B';
    heads->bmp_magic.signature[1] = 'M';
    heads->bmp_header.data_offset = ql::bmp::FILEs;
    heads->bmp_header.file_size = width * height * bps + ql::bmp::FILEs;

    heads->dib_header.compression = ql::bmp::BI_RGB;
    heads->dib_header.colors_used = 0;
    heads->dib_header.bits_per_pixel = bps*8;
    heads->dib_header.planes = 1;
    heads->dib_header.size = ql::bmp::DIBs;
    heads->dib_header.image_size = 0;
    heads->dib_header.important_colors = 0;
    heads->dib_header.x_pixels_per_meter = 2835;
    heads->dib_header.y_pixels_per_meter = 2835;
    heads->dib_header.width = width;
    heads->dib_header.height = height;
}

void ql::bmp::readImage(FILE* f, ql::bmp::Headers* head, ql::uint8_t* pixels) {
    fseek(f,head->bmp_header.data_offset,SEEK_SET);

    //ql::uint32_t px_p_b = head->dib_header.bits_per_pixel/8;
    //ql::uint32_t size = head->dib_header.width * head->dib_header.height * px_p_b;

    fread(pixels,1,head->bmp_header.file_size - ql::bmp::FILEs,f);

}

void ql::bmp::writeImage(FILE* f, ql::bmp::Headers* heads, const ql::uint8_t* pixels) {
    fseek(f,0,SEEK_SET);

    fwrite(heads,1,ql::bmp::FILEs,f);

    fwrite(pixels, 1, heads->bmp_header.file_size - ql::bmp::FILEs, f);
}