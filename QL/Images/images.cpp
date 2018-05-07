#include "images.hpp"

#include <cstdint>
#include <string.h>
#include <stdlib.h>

/*Image formats libraries*/

#include <jpeglib.h>
#include <png.h>
#include <tiffio.h>

#include <iostream>

std::string ql::readFormat(const char* format) {
    //std::cout << format << '\n';
    const char* f2 = format;
    while(*f2 != '\0') {
        if(*f2 == '.') return readFormat(f2+1);
        f2++;
    }
    return std::string(format);
}
