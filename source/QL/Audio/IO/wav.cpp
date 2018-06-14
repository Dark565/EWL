#include <QL/Audio/audio.hpp>

#include <QL/Formats/wav.hpp>
#include <string.h>

bool ql::SoundBuffer::exportToWAV(const char* path) const {
    if(isLegit()) {
        FILE* f;
        if(f = fopen(path,"w")) {

            ql::wav::WAVE_Header head;
            ql::wav::constructHeaders(&head, bytes_per_sample*8, sample_rate, channels, size);

            ql::wav::writeData(f,&head, samples);

            return true;

        }

        fclose(f);

        return false;
    }

    return false;
}

bool ql::SoundBuffer::loadFromWAV(const char* path) {

    FILE* f;
    if(f = fopen(path,"r")) {

        bool gd;

        ql::wav::WAVE_Header head;
        if(gd = (!ql::wav::loadHeaders(f, &head))) {


            if (gd = (!memcmp(head.riff_c.format, "WAVE",4))) {
                destroy();

                bytes_per_sample = head.fmt_c.bits_per_sample/8;
                sample_rate = head.fmt_c.sample_rate;
                size = head.data_c.subchunk2_size;
                channels = head.fmt_c.num_channels;

                samples = (uint8_t*)malloc(head.data_c.subchunk2_size);

                ql::wav::readData(f, &head, samples);

            }

        }

        fclose(f);

        return gd;

    }
    return false;
}

bool ql::SoundBuffer::insertFromWAV(const char* path, uint32_t pos) {
    FILE* f;
    if(f = fopen(path, "r")) {

        bool gd;
        
        ql::wav::WAVE_Header head;
        if(gd = (!ql::wav::loadHeaders(f, &head))) {

            if(gd = !(memcmp(head.riff_c.format, "WAVE",4))) {
                samples = (uint8_t*)realloc(samples, size + head.data_c.subchunk2_size);
                memmove(samples+pos+head.data_c.subchunk2_size, samples+pos, size-pos);
                
                ql::wav::readData(f, &head, samples+pos);

                size += head.data_c.subchunk2_size;
            }

        }

        fclose(f);

        return gd;
    }
    return false;
}