#pragma once

#include <stdint.h>
#include <stdio.h>

namespace ql {
    namespace bmp {
        enum compressions {
            BI_RGB,
            BI_RLE,
            BI_RLE4
        };

        enum {
            Magics = 2,
            BMPs = 12,
            DIBs = 40,
            FILEs = Magics + BMPs + DIBs
        };

        struct BMPMagic {
            char signature[2];
        };

        struct BMPHeader {
            uint32_t file_size;
            uint32_t reserved;
            uint32_t data_offset;
        };

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

        };

        struct Headers {
            struct BMPMagic bmp_magic;
            struct BMPHeader bmp_header;
            struct DIBHeader dib_header;
        };

        void constructHeaders(struct Headers* heads, uint32_t width, uint32_t height);
        void loadHeaders(FILE* f, struct Headers* heads);
        void writeImage(FILE* f, struct Headers* heads, const uint8_t* pixels);
        void readImage(FILE* f, struct Headers* head, uint8_t* pixels);
    }
}