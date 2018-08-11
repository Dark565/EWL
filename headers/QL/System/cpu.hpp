#pragma once

#include <QL/Definitions/int.hpp>

#include <string>

namespace ql  {
    namespace cpu {

        enum input {
            VENDOR      = 0x00000000,
            PROC_NAME_1 = 0x80000002,
            PROC_NAME_2 = 0x80000003,
            PROC_NAME_3 = 0x80000004

        };

        /* CPUID processor instruction */   
        void cpuid(uint32_t, uint32_t[4]);
        
        /* Gets processor vendor */
        std::string getVendor();

        /* Gets processor model */
        std::string getName();

    }
}