#include <stddef.h>

template <class T>
inline bool ewl::SoundBuffer::setSample(T sample, uint32_t x) {
    if(isLegit()) {
        *(((T*)samples)+x) = sample;
        return false;
    }
    return false;
}

template <class T>
inline T* ewl::SoundBuffer::getSample(uint32_t x) const {
    if(isLegit()) {
        return ((T*)samples)+x;
    }
    return NULL;
}

inline bool ewl::SoundBuffer::isGood() const {
    return isLegit();
}

constexpr ewl::uint32_t ewl::SoundBuffer::getSamplesCount() {
    return size / bytes_per_sample;
}

constexpr ewl::uint32_t ewl::SoundBuffer::bytesPerSecond() {
    return sample_rate * channels * bytes_per_sample;
}