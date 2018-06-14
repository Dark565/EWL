#include <QL/Audio/audio.hpp>

#include <stdlib.h>
#include <string.h>

bool ql::SoundBuffer::create(uint32_t samples_a, uint16_t bps_a, uint32_t sample_rate_a, uint8_t channels_a) {
    destroy();

    samples = (uint8_t*)malloc(samples_a*bps_a*channels_a);
    bytes_per_sample = bps_a;
    sample_rate = sample_rate_a;
    channels = channels_a;

    size = samples_a * bps_a * channels;
}

bool ql::SoundBuffer::destroy() {
    if(isLegit() && isDestroyable()) {
        free(samples);
        samples = NULL;
        bytes_per_sample = 0;
        sample_rate = 0;
        channels = 0;
        size = 0;
        flags = 0;
        return true;
    }
    return false;
}

bool ql::SoundBuffer::insert(uint8_t* bytes, uint32_t num, uint32_t pos) {
    samples = (uint8_t*)realloc(samples,size+num);

    memmove(samples+pos+num,samples+pos,size-pos);
    memcpy(samples+pos,bytes,num);

    size += num;

    return true;
}

bool ql::SoundBuffer::insert(const ql::SoundBuffer& buff, uint32_t pos) {
    if(buff.isLegit()) {
        samples = (uint8_t*)realloc(samples,size+buff.size);

        memmove(samples+pos+buff.size,samples+pos,size-pos);
        memcpy(samples+pos, buff.samples, buff.size);

        size += buff.size;

        return true;
    }
    return false;
}

bool ql::SoundBuffer::isLegit() const {
    return samples;
}

bool ql::SoundBuffer::setSampleByte(uint8_t byte, uint32_t x) {
    if(isLegit()) {
        samples[x] = byte;

        return true;
    }
    return false;
}

uint8_t* ql::SoundBuffer::getSampleByte(uint32_t x) const {
    if(isLegit()) {
        return samples+x;
    }
    return NULL;
}

const uint8_t* ql::SoundBuffer::getSamplesPtr() const {
    return samples;
}

bool ql::SoundBuffer::isDestroyable() const {
    return (flags & 1);
}

bool ql::SoundBuffer::setNonDestroyablePtr(uint8_t* ptr, uint32_t size, uint32_t bps_a, uint32_t sample_rate_a, uint8_t channels_a) {
    destroy();
    
    samples = ptr;
    size = size;
    bytes_per_sample = bps_a;
    sample_rate = sample_rate_a;
    channels = channels_a;

    flags |= 1;
}

void ql::SoundBuffer::init() {
    samples = NULL;
    size = 0;
    sample_rate = 0;
    bytes_per_sample = 0;

}

ql::SoundBuffer::SoundBuffer() {
    init();
}

ql::SoundBuffer::~SoundBuffer() {
    destroy();
}