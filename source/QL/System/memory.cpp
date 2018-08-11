#include <QL/System/memory.hpp>
#include <QL/Definitions/int.hpp>

#include <stdlib.h>

ql::size_t ql::memory::filterForRange(const void* in, void* out, ql::size_t ds, const ql::uint8_t* ranges, ql::size_t size) {

    const   ql::uint8_t* b_in = (const ql::uint8_t*)in;
            ql::uint8_t* b_out = (ql::uint8_t*)out;

    uint32_t b_num = 0;
    for(ql::uint32_t i = 0; i < ds; i++) {
        ql::uint8_t byte = b_in[i];
        for(ql::uint32_t j = 0; j < size*2; j+=2) {
            if(byte >= ranges[j] && byte <= ranges[j+1]) {
                b_out[b_num] = byte;
                b_num++;
                break;
            }
        }
    }

    return b_num;

}