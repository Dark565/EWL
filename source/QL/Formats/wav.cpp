#include <QL/Formats/wav.hpp>
#include <string.h>

void ql::wav::loadHeaders(FILE* f, ql::wav::WAVE_Header* head) {
    fseek(f,0,SEEK_SET);
    fread(&head->riff_c, 1, ql::wav::RIFF_s, f);
    fread(&head->fmt_c, 1, ql::wav::FMT_s, f);
    fread(&head->data_c, 1, ql::wav::DATA_s, f);
}

void ql::wav::constructHeaders(ql::wav::WAVE_Header* head, uint16_t bits_per_sample, uint16_t sample_rate, uint8_t channels, uint32_t samples) {
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
    head->data_c.subchunk2_size = samples * channels * bits_per_sample / 8;

    head->riff_c.chunk_size = 36 + head->data_c.subchunk2_size;
}

void ql::wav::readData(FILE* f, WAVE_Header* head, uint8_t* bytes) {
    fseek(f,44,SEEK_SET);
    fread(bytes, 1, head->data_c.subchunk2_size, f);
}

void ql::wav::writeData(FILE* f, WAVE_Header* head, const uint8_t* bytes) {
    fseek(f, 0, SEEK_SET);
    fwrite(&head->riff_c, 1, ql::wav::RIFF_s, f);
    fwrite(&head->fmt_c, 1, ql::wav::FMT_s, f);
    fwrite(&head->data_c, 1, ql::wav::DATA_s, f);

    fseek(f,44,SEEK_SET);
    fwrite(bytes, 1, head->data_c.subchunk2_size, f);
}