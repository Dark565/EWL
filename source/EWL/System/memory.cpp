#include <EWL/System/memory.hpp>
#include <EWL/Definitions/int.hpp>

#include <stdlib.h>

ewl::size_t ewl::memory::filterByRange(const void* in, void* out, ewl::size_t ds, const ewl::uint8_t* ranges, ewl::size_t size) {

    const   ewl::uint8_t* b_in = (const ewl::uint8_t*)in;
            ewl::uint8_t* b_out = (ewl::uint8_t*)out;

    uint32_t b_num = 0;
    for(ewl::uint32_t i = 0; i < ds; i++) {
        ewl::uint8_t byte = b_in[i];
        for(ewl::uint32_t j = 0; j < size*2; j+=2) {
            if(byte >= ranges[j] && byte <= ranges[j+1]) {
                b_out[b_num] = byte;
                b_num++;
                break;
            }
        }
    }

    return b_num;

}