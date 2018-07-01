#pragma once

#include <cstdint>
#include <string>

#include <QL/Graphics/Colorize/colors.hpp>
#include <QL/Graphics/Compress/compressors.hpp>
#include <QL/Definitions/Arrays/array.hpp>


namespace ql {
    class Pixmap {
        uint8_t* pixels;
        uint32_t size_x, size_y;
        bool deletable;
        uint32_t bytes_per_pixel;

        bool compressed;

        /*Data compressor*/

        Compressor* compressor;


    public:

        enum Channels {
            C_R = 1,
            C_G = 2,
            C_B = 4,
            C_A = 8,
            C_RGB = C_R | C_G | C_B,
            C_RGBA = C_R | C_G | C_B | C_A

        };

        enum Bytes {
            B_RGB = 3,
            B_RGBA = 4,
            B_MAX_256 = 1
        };
        
        /*Creates image filled with color*/

        void create(uint32_t size_x, uint32_t size_y, const Pixel& col = Black, uint32_t bpp = Bytes::B_RGBA);

        /*Copies pixmap but only with channels in 'ch'*/

        Pixmap constructLesser(uint64_t ch, uint32_t ch_count) const;

        /*Copies pixmap with other bytes per pixel count*/

        Pixmap constructDecreased(uint32_t ch_count) const;

        /*Sets compressor*/
        /*If you don't wanna have any compressor set it to NULL*/

        void setCompressor(Compressor* comp);

        /*Gets compressor*/

        Compressor* getCompressor() const;

        /*Compress the image with set compressor or not if compressor is NULL or image is already compressed*/

        bool compress();

        /*Decompress compressed image or not if compressor is NULL or image is not compressed*/

        bool decompress();

        /*Removes image from memory
        /Doesn't work if image doesn't exist and doesn't free memory if pointer is non-deletable */

        bool destroy();

        /*Gets pixel array pointer*/

        const uint8_t* getPixelPtr();

        /*Scales the image to new sizes*/

        bool scale(uint32_t n_x, uint32_t n_y);

        /*Merges image on coordinates given in arguments*/

        bool merge(const Pixmap& ap, uint32_t ax, uint32_t ay, bool EXCLUDE_ALPHA = false);

        /*Cuts image to the coordinates*/

        bool cut(uint32_t from_x, uint32_t from_y, uint32_t to_x, uint32_t to_y);

        /*Rotates the image*/

        bool rotate(float rad, Pixel emptyColor = Alpha);

        /*Replaces all pixels with the color on different color*/

        bool replaceColor(const ql::Pixel& a, const ql::Pixel& b);

        /*Gets width of the image*/

        uint32_t getWidth() const;

        /*Gets height of the image*/

        uint32_t getHeight() const;

        /*Gets count of the pixels*/

        uint32_t getSize() const;

        /*Gets number of bytes per pixel*/

        uint32_t getBytesPerPixel() const;

        /*Checks does image exist*/

        bool isLegit() const;

        /*Checks is the image deletable*/

        bool isDeletable() const;

        /*Sets the color for the whole image*/

        bool setGlobalColor(const Pixel& pix, uint8_t color_channel);

        /*Sets pixel on axis x,y*/

        bool setPixelXY(uint32_t x, uint32_t y, const Pixel& col);

        /*Sets pixel on axis x
        /if you'll go beyond x axis you'll work on increased y axis*/  

        bool setPixelX(uint32_t x, const Pixel& col);

        /*Sets pixel on axis y
        /if you'll go beyond y axis you'll work on increased x axis*/

        bool setPixelY(uint32_t y, const Pixel& col);

        /*Gets careful pixel*/

        Pixel getPixelXCareful(uint32_t x) const;

        /*Gets pixel color on axis x,y*/

        Pixel& getPixelXY(uint32_t x, uint32_t y) const;

        /*Gets pixel color on axis x*/

        Pixel& getPixelX(uint32_t x) const;

        /*Gets pixel color on axis y*/

        Pixel& getPixelY(uint32_t y) const;

        /*Loads the image from files*/

        bool loadFromTIFF(const char* path);
        bool loadFromPNG(const char* path);
        bool loadFromJPEG(const char* path);
        bool loadFromBMP(const char* path);
        
        /*Exports the image to files*/

        bool exportToTIFF(const char* path) const;
        bool exportToPNG(const char* path) const;
        bool exportToJPEG(const char* path) const;
        bool exportToBMP(const char* path) const;

        /*Draws a circle*/

        bool drawCircle(float radius, int sensitivity, int middle_x, int middle_y, const Pixel& col);

        /*Sets a new pixels pointer as non-deletable
        /Removes existing image*/

        void setNonDeletableFromMemory(uint8_t* ptr, uint32_t x, uint32_t y, uint32_t bpp = Bytes::B_RGBA);

        /*Sets a new pixels pointer as deletable
        /Removes existing image*/

        void setDeletableFromMemory(uint8_t* ptr, uint32_t x, uint32_t y, uint32_t bpp = Bytes::B_RGBA);

        /*Copies pixels from other pixmap to issuing one*/

        bool copy(const ql::Pixmap& from, bool COPY_BPP_VALUE = true);
        Pixmap& operator=(const Pixmap& pix);
        Pixmap(const Pixmap&);

        //Default constructor

        Pixmap();

        /*Calls destroy() to remove the image from memory*/

        ~Pixmap();

    protected:
        void init();

    };
}