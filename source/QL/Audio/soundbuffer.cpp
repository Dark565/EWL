#include <QL/Audio/soundbuffer.hpp>

#include <stdlib.h>
#include <string.h>

bool ql::SoundBuffer::create(ql::uint32_t samples_a, ql::uint16_t bps_a, ql::uint32_t sample_rate_a, ql::uint8_t channels_a) {
    destroy();

    samples = (ql::uint8_t*)malloc(samples_a*bps_a*channels_a);
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

bool ql::SoundBuffer::insert(ql::uint8_t* bytes, ql::uint32_t num, ql::uint32_t pos) {
    samples = (ql::uint8_t*)realloc(samples,size+num);

    memmove(samples+pos+num,samples+pos,size-pos);
    memcpy(samples+pos,bytes,num);

    size += num;

    return true;
}

bool ql::SoundBuffer::insert(const ql::SoundBuffer& buff, ql::uint32_t pos) {
    if(buff.isLegit()) {
        insert(buff.samples,buff.size,pos);
    }
    return false;
}

bool ql::SoundBuffer::isLegit() const {
    return samples;
}

bool ql::SoundBuffer::setSampleByte(ql::uint8_t byte, ql::uint32_t x) {
    if(isLegit()) {
        samples[x] = byte;

        return true;
    }
    return false;
}

ql::uint8_t* ql::SoundBuffer::getSampleByte(ql::uint32_t x) const {
    if(isLegit()) {
        return samples+x;
    }
    return NULL;
}

const ql::uint8_t* ql::SoundBuffer::getSamplesPtr() const {
    return samples;
}

bool ql::SoundBuffer::isDestroyable() const {
    return (flags & 1);
}

bool ql::SoundBuffer::setNonDestroyablePtr(ql::uint8_t* ptr, ql::uint32_t size, ql::uint32_t bps_a, ql::uint32_t sample_rate_a, ql::uint8_t channels_a) {
    destroy();
    
    samples = ptr;
    size = size;
    bytes_per_sample = bps_a;
    sample_rate = sample_rate_a;
    channels = channels_a;

    flags |= 1;
}

ql::SoundBuffer::SoundBuffer() {
    samples = NULL;
    size = 0;
    sample_rate = 0;
    bytes_per_sample = 0;
}

ql::SoundBuffer::~SoundBuffer() {
    destroy();
}