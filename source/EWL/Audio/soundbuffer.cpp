#include <EWL/Audio/soundbuffer.hpp>

#include <stdlib.h>
#include <string.h>

void ewl::SoundBuffer::create(ewl::uint32_t samples_a, ewl::uint16_t bps_a, ewl::uint32_t sample_rate_a, ewl::uint8_t channels_a) {
    destroy();

    samples = (ewl::uint8_t*)malloc(samples_a*bps_a*channels_a);
    bytes_per_sample = bps_a;
    sample_rate = sample_rate_a;
    channels = channels_a;

    size = samples_a * bps_a * channels;
}

bool ewl::SoundBuffer::destroy() {
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

bool ewl::SoundBuffer::insert(ewl::uint8_t* bytes, ewl::uint32_t num, ewl::uint32_t pos) {
    samples = (ewl::uint8_t*)realloc(samples,size+num);

    memmove(samples+pos+num,samples+pos,size-pos);
    memcpy(samples+pos,bytes,num);

    size += num;

    return true;
}

bool ewl::SoundBuffer::insert(const ewl::SoundBuffer& buff, ewl::uint32_t pos) {
    if(buff.isLegit()) {
        insert(buff.samples,buff.size,pos);
    }
    return false;
}

bool ewl::SoundBuffer::isLegit() const {
    return samples;
}

bool ewl::SoundBuffer::setSampleByte(ewl::uint8_t byte, ewl::uint32_t x) {
    if(isLegit()) {
        samples[x] = byte;

        return true;
    }
    return false;
}

ewl::uint8_t* ewl::SoundBuffer::getSampleByte(ewl::uint32_t x) const {
    if(isLegit()) {
        return samples+x;
    }
    return NULL;
}

const ewl::uint8_t* ewl::SoundBuffer::getSamplesPtr() const {
    return samples;
}

bool ewl::SoundBuffer::isDestroyable() const {
    return (flags & 1);
}

void ewl::SoundBuffer::setNonDestroyablePtr(ewl::uint8_t* ptr, ewl::uint32_t size, ewl::uint32_t bps_a, ewl::uint32_t sample_rate_a, ewl::uint8_t channels_a) {
    destroy();
    
    samples = ptr;
    size = size;
    bytes_per_sample = bps_a;
    sample_rate = sample_rate_a;
    channels = channels_a;

    flags |= 1;
}

ewl::SoundBuffer::SoundBuffer() {
    samples = NULL;
    size = 0;
    sample_rate = 0;
    bytes_per_sample = 0;
}

ewl::SoundBuffer::~SoundBuffer() {
    destroy();
}