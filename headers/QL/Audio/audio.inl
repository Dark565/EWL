#include <stdlib.h>

template <class T>
inline bool ql::SoundBuffer::setSample(T sample, uint32_t x) {
    if(isLegit()) {
        *(((T*)samples)+x) = sample;
        return false;
    }
    return false;
}

template <class T>
inline T* ql::SoundBuffer::getSample(uint32_t x) const {
    if(isLegit()) {
        return ((T*)samples)+x;
    }
    return NULL;
}

inline bool ql::SoundBuffer::isGood() const {
    return isLegit();
}

constexpr uint32_t ql::SoundBuffer::getSamplesCount() {
    return getBytesCount() / getChannelsCount() / getBPS();
}

constexpr uint32_t ql::SoundBuffer::getBytesCount() {
    return size;
}

constexpr uint16_t ql::SoundBuffer::getBPS() {
    return bytes_per_sample;
}

constexpr uint32_t ql::SoundBuffer::getSampleRate() {
    return sample_rate;
}

constexpr uint8_t ql::SoundBuffer::getChannelsCount() {
    return channels;
}

constexpr uint8_t ql::SoundBuffer::getFlags() {
    return flags;
}

constexpr uint32_t ql::SoundBuffer::bytesPerSecond() {
    return getSampleRate() * getBPS() * getChannelsCount();
}