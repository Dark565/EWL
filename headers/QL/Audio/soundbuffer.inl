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

constexpr uint32_t ql::SoundBuffer::bytesPerSecond() {
    return getSampleRate() * getBPS() * getChannelsCount();
}