#include <EWL/Formats/wav.hpp>
#include <string.h>

ewl::uint8_t ewl::wav::loadHeaders(FILE* f, ewl::wav::WAVE_Header* head) {
    fseek(f,0,SEEK_SET);
    fread(&head->riff_c, 1, ewl::wav::RIFF_s, f);
    fread(&head->fmt_c, 1, ewl::wav::FMT_s, f);

    ewl::uint32_t p = ftell(f);
    char d[4];
    do {
        if(!feof(f)) {
            
            fseek(f,p++,SEEK_SET);
            fread(d,1,4,f);

        } else return ewl::wav::LOAD_DATA_ERROR;
    } while(memcmp(d,"data",4) != 0);

    fseek(f,p-1,SEEK_SET);

    fread(&head->data_c, 1, ewl::wav::DATA_s, f);

    head->d_position = ftell(f);

    return 0;
}

void ewl::wav::constructHeaders(ewl::wav::WAVE_Header* head, ewl::uint16_t bits_per_sample, ewl::uint16_t sample_rate, ewl::uint8_t channels, ewl::uint32_t samples) {
    memcpy(head->riff_c.chunk_id, "RIFF", 4);
    memcpy(head->riff_c.format, "WAVE", 4);

    memcpy(head->fmt_c.subchunk1_id, "fmt ", 4);
    head->fmt_c.subchunk1_size = 16;
    head->fmt_c.audio_format = 1;
    head->fmt_c.num_channels = channels;
    head->fmt_c.sample_rate = sample_rate;
    head->fmt_c.byte_rate = sample_rate * channels * bits_per_sample / 8;
    head->fmt_c.block_align = channels * bits_per_sample / 8;
    head->fmt_c.bits_per_sample = bits_per_sample;

    memcpy(head->data_c.subchunk2_id, "data", 4);
    head->data_c.subchunk2_size = samples;

    head->riff_c.chunk_size = 36 + head->data_c.subchunk2_size;

    head->d_position = 44;
}

void ewl::wav::readData(FILE* f, WAVE_Header* head, ewl::uint8_t* bytes) {
    fseek(f,head->d_position,SEEK_SET);
    fread(bytes, 1, head->data_c.subchunk2_size, f);
}

void ewl::wav::writeData(FILE* f, WAVE_Header* head, const ewl::uint8_t* bytes) {
    fseek(f, 0, SEEK_SET);
    fwrite(&head->riff_c, 1, ewl::wav::RIFF_s, f);
    fwrite(&head->fmt_c, 1, ewl::wav::FMT_s, f);
    fwrite(&head->data_c, 1, ewl::wav::DATA_s, f);

    fseek(f,head->d_position,SEEK_SET);
    fwrite(bytes, 1, head->data_c.subchunk2_size, f);
}