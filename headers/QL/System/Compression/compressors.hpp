#pragma once

#include <QL/Definitions/int.hpp>

/*Compressors header*/

namespace ql {
    namespace Compress {

        struct Data {
            void* data;
            size_t size;
        };

    }

    class Compressor {
            public:

                virtual Compress::Data Compress(void* data, size_t size) {};
                virtual Compress::Data Decompress(void* data, size_t size) {};

            private:
                Compressor() = default;
    };

    namespace Compress {

        class zlib : public Compressor {
            public:
                virtual Data Compress(void* data, size_t size);
                virtual Data Decompress(void* data, size_t size);
        };

        class bz2 : public Compressor {
            public:
                virtual Data Compress(void* data, size_t size);
                virtual Data Decompress(void* data, size_t size);
        };

        class _7z : public Compressor {
            public:
                virtual Data Compress(void* data, size_t size);
                virtual Data Decompress(void* data, size_t size);
        };
    }

}