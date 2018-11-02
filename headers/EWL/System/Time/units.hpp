#pragma once
#include <EWL/Definitions/int.hpp>

namespace ewl {
    struct us;
    struct ms;
    struct sec;

    struct Time {
        uint64_t t;

        struct us {
            uint64_t t;
            us(uint64_t a) : t(a) {}
        };

        struct ms {
            uint64_t t;
            ms(uint64_t a) : t(a) {}
        };

        struct sec {
            float32_t t;
            sec(float32_t a) : t(a) {}
        };

        Time& operator=(const us& a);
        Time& operator=(const ms& a);
        Time& operator=(const sec& a);

        Time(const us& a);
        Time(const ms& a);
        Time(const sec& a);

        us getUS();
        ms getMS();
        sec getSEC();
    };

    typedef Time ns;
}