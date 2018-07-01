#pragma once

#include <QL/Definitions/defs.hpp>

#if defined(__QL_OS_UNIX) && !defined(__QL_OS_MACOS) && !defined(__QL_OS_ANDROID)
    #define __QL_WINSERVER_XORG

#elif defined(__QL_OS_WINDOWS)
    #define __QL_WINSERVER_WINAPI

//elif defined ...
#endif
