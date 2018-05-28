#pragma once

#include "../Definitions/defs.hpp"

#if defined  __QL_OS_WINDOWS
    #include "Win32/types.hpp"
#else
    #include "PosixThread/types.hpp"
#endif