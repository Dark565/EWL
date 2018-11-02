#include <EWL/Audio/soundbuffer.hpp>

#include <EWL/Formats/wav.hpp>
#include <string.h>

bool ewl::SoundBuffer::exportToWAV(const char* path) const {
    if(isLegit()) {
        FILE* f;
        if(f = fopen(path,"w")) {

            ewl::wav::WAVE_Header head;
            ewl::wav::constructHeaders(&head, bytes_per_sample*8, sample_rate, channels, size);

            ewl::wav::writeData(f,&head, samples);

            return true;

        }

        fclose(f);

        return false;
    }

    return false;
}

bool ewl::SoundBuffer::loadFromWAV(const char* path) {

    FILE* f;
    if(f = fopen(path,"r")) {

        bool gd;

        ewl::wav::WAVE_Header head;
        if(gd = (!ewl::wav::loadHeaders(f, &head))) {


            if (gd = (!memcmp(head.riff_c.format, "WAVE",4))) {
                destroy();

                bytes_per_sample = head.fmt_c.bits_per_sample/8;
                sample_rate = head.fmt_c.sample_rate;
                size = head.data_c.subchunk2_size;
                channels = head.fmt_c.num_channels;

                samples = (ewl::uint8_t*)malloc(head.data_c.subchunk2_size);

                ewl::wav::readData(f, &head, samples);

            }

        }

        fclose(f);

        return gd;

    }
    return false;
}

bool ewl::SoundBuffer::insertFromWAV(const char* path, ewl::uint32_t pos) {
    FILE* f;
    if(f = fopen(path, "r")) {

        bool gd;
        
        ewl::wav::WAVE_Header head;
        if(gd = (!ewl::wav::loadHeaders(f, &head))) {

            if(gd = !(memcmp(head.riff_c.format, "WAVE",4))) {
                samples = (ewl::uint8_t*)realloc(samples, size + head.data_c.subchunk2_size);
                memmove(samples+pos+head.data_c.subchunk2_size, samples+pos, size-pos);
                
                ewl::wav::readData(f, &head, samples+pos);

                size += head.data_c.subchunk2_size;
            }

        }

        fclose(f);

        return gd;
    }
    return false;
}