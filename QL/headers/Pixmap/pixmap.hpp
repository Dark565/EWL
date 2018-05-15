#pragma once

#include <cstdint>
#include <string>

#include <Colorize/colors.hpp>
#include <Compress/compressors.hpp>
#include <Arrays/array.hpp>


namespace ql {
    class Pixmap {
        uint32_t* pixels;
        uint32_t size_x, size_y;
        bool deletable;

        bool compressed;

        /*Data compressor*/

        Compressor* compressor;


    public:

        enum Channels {
            R = 1,
            G = 2,
            B = 4,
            A = 8,
            RGBA = 15

        };
        
        /*Creates image filled with color*/

        void create(uint32_t size_x, uint32_t size_y, const Pixel& col = Black);

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

        const uint32_t* getPixelPtr();

        /*Scales the image to new sizes*/

        bool scale(uint32_t n_x, uint32_t n_y);

        /*Merges image on taken coordinates*/

        bool merge(const Pixmap& ap, uint32_t ax, uint32_t ay, bool EXCLUDE_ALPHA = false);

        /*Puts gaussian blur on the image with taken density*/

        bool blur(float density);

        /*Changes image perspective*/

        bool perspectiveProjection(Array<Array<float,3>,4> angles);

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

        /*Checks does image exist*/

        bool isLegit() const;
        #define isGood isLegit

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

        /*Gets pixel color on axis x,y*/

        Pixel& getPixelXY(uint32_t x, uint32_t y) const;

        /*Gets pixel color on axis x*/

        Pixel& getPixelX(uint32_t x) const;

        /*Gets pixel color on axis y*/

        Pixel& getPixelY(uint32_t y) const;

        /*Loads image from file formats*/

        bool loadFromTIFF(const char* path);
        bool loadFromPNG(const char* path);
        bool loadFromJPEG(const char* path);
        
        /*Exports to file formats*/

        bool exportToTIFF(const char* path) const;
        bool exportToPNG(const char* path) const;
        bool exportToJPEG(const char* path) const;

        /*Draw circle*/

        bool drawCircle(float radius, int sensitivity, int middle_x, int middle_y, const Pixel& col);

        /*Sets new pixels pointer as non-deletable
        /Removes existing image*/

        void setNonDeletableFromMemory(uint32_t* ptr, uint32_t x, uint32_t y);

        /*Sets new pixels pointer as deletable
        /Removes existing image*/

        void setDeletableFromMemory(uint32_t* ptr, uint32_t x, uint32_t y);

        /*Copies pixels from other pixmap to issuing one*/

        Pixmap& operator=(const Pixmap& pix);
        Pixmap(const Pixmap&);

        //Default constructor

        Pixmap();

        /*Calls destroy() on existing image to remove it from memory*/

        ~Pixmap();

    protected:
        void init();

    };
}