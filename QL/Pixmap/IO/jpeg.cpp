#include "../pixmap.hpp"

#include <jpeglib.h>

bool ql::Pixmap::loadFromJPEG(const char* path) {
    jpeg_decompress_struct j_c;
    jpeg_error_mgr j_e;

    FILE* f;
    JSAMPARRAY buff;

    if((f = fopen(path,"rb")) == NULL) {
        return 0;
    }

    jpeg_create_decompress(&j_c);

    jpeg_stdio_src(&j_c,f);

    jpeg_read_header(&j_c, TRUE);

    jpeg_start_decompress(&j_c);

    int row_width = j_c.output_width * j_c.out_color_components;
    buff = (*j_c.mem->alloc_sarray)((j_common_ptr)&j_c,JPOOL_IMAGE,row_width,1);

    while(j_c.output_scanline < j_c.output_height) {
        jpeg_read_scanlines(&j_c, buff, 1);
    }

    jpeg_finish_decompress(&j_c);
    jpeg_destroy_decompress(&j_c);

    return 1;

}