#pragma once

#include <Definitions/defs.hpp>

#if defined __QL_OS_LINUX || defined __QL_OS_FREEBSD
    #include "Unix/types.hpp"
#elif defined __QL_OS_WINDOWS
    #include "WIN32/types.hpp"
#elif defined __QL_OS_APPLE
    //
#elif defined __QL_OS_ANDROID
    //
#elif defined __QL_OS_NOTSUPPORTED
    #include "Nothing/types.hpp"
    #error Your operating system is not supported by QL
#endif