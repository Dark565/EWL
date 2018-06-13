#pragma once

#include <stdint.h>

namespace ql {
    class SoundBuffer {

        uint8_t* samples;
        uint16_t bytes_per_sample;
        uint32_t sample_rate;
        uint32_t size;
        uint8_t channels;

        bool flags;

    public:

        /* Allocates memory for the buffer */

        bool create(uint32_t samples_a, uint16_t bps_a, uint32_t sample_rate_a, uint8_t channels_a);

        /* Removes the buffer */

        bool destroy();

        /* Inserts samples into existing table and resizes it */

        bool insert(uint8_t* bytes, uint32_t num, uint32_t pos);
        bool insert(const SoundBuffer& buff, uint32_t pos);

        /* Checks is buffer's memory allocated */

        bool isLegit() const;
        inline bool isGood() const;

        /* Gets sample byte */

        bool setSampleByte(uint8_t byte, uint32_t x);
        uint8_t* getSampleByte(uint32_t x) const;

        /* Gets size of the buffer in bytes */

        constexpr uint32_t getSize();

        /* Gets bytes per sample */

        constexpr uint16_t getBPS();

        /* Gets sample rate */

        constexpr uint32_t getSampleRate();

        /* Get channels count */

        constexpr uint8_t getChannelsCount();

        /* Gets flags of the buffer */

        constexpr uint8_t getFlags();


        /* Gets sample with specified type */

        template <class T> inline bool setSample(T sample, uint32_t x);
        template <class T> inline T* getSample(uint32_t x) const;

        /* Returns pointer to samples table */

        const uint8_t* getSamplesPtr() const;

        /* IO Functions*/

        bool exportToWAV(const char* path) const;
        bool loadFromWAV(const char* path);

        /* Checks is buffer destroyable */

        bool isDestroyable() const;

        bool setNonDestroyablePtr(uint8_t* ptr_a, uint32_t size_a, uint32_t bps_a, uint32_t sample_rate_a, uint8_t channels_a);

        SoundBuffer();

    protected:

        void init();
        
    };
}

#include "audio.inl"