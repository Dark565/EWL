#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

namespace ql {
    namespace wav {
        enum {
            RIFF_s = 12,
            FMT_s = 24,
            DATA_s = 8,
            ALL_s = RIFF_s + FMT_s + DATA_s
        };

        struct RIFF_Chkdes {
            char chunk_id[4];
            uint32_t chunk_size;
            char format[4];
        };
        struct FMT_Chunk {
            char subchunk1_id[4];
            uint32_t subchunk1_size;
            uint16_t audio_format;
            uint16_t num_channels;
            uint32_t sample_rate;
            uint32_t byte_rate;
            uint16_t block_align;
            uint16_t bits_per_sample;
        };
        struct DATA_Chunk {
            char subchunk2_id[4];
            uint32_t subchunk2_size;
        };

        struct WAVE_Header {
            RIFF_Chkdes riff_c;
            FMT_Chunk fmt_c;
            DATA_Chunk data_c;
        };

        void constructHeaders(WAVE_Header* head, uint16_t bits_per_sample, uint16_t sample_rate, uint8_t channels, uint32_t samples);
        void loadHeaders(FILE* f, WAVE_Header* head);
        void readData(FILE* f, WAVE_Header* head, uint8_t* bytes);
        void writeData(FILE* f, WAVE_Header* head, const uint8_t* bytes);
    }
}