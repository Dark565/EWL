#pragma once

#include <QL/Definitions/int.hpp>
#include <stdio.h>

#include <QL/Definitions/compiller.hpp>

namespace ql {
    namespace bmp {
        enum compressions {
            BI_RGB,
            BI_RLE,
            BI_RLE4
        };


        struct BMPMagic {
            char signature[2];
        } QL_ATR_PACKED;

        struct BMPHeader {
            uint32_t file_size;
            uint32_t reserved;
            uint32_t data_offset;
        } QL_ATR_PACKED;

        struct DIBHeader {
            uint32_t size;
            uint32_t width;
            uint32_t height;
            uint16_t planes;
            uint16_t bits_per_pixel;
            uint32_t compression;
            uint32_t image_size;
            uint32_t x_pixels_per_meter;
            uint32_t y_pixels_per_meter;
            uint32_t colors_used;
            uint32_t important_colors;

        } QL_ATR_PACKED;

        struct Headers {
            struct BMPMagic bmp_magic;
            struct BMPHeader bmp_header;
            struct DIBHeader dib_header;
        } QL_ATR_PACKED;

        enum {
            Magics  = sizeof(BMPMagic),
            BMPs    = sizeof(BMPHeader),
            DIBs    = sizeof(DIBHeader),
            FILEs   = Magics + BMPs + DIBs
        };

        void constructHeaders(struct Headers* heads, uint32_t width, uint32_t height, uint32_t bps);
        void loadHeaders(FILE* f, struct Headers* heads);
        void writeImage(FILE* f, struct Headers* heads, const uint8_t* pixels);
        void readImage(FILE* f, struct Headers* head, uint8_t* pixels);
    }
}