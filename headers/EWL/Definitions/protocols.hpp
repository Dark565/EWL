#pragma once

#include "os.hpp"

#if defined(__EWL_OS_UNIX) && !defined(__EWL_OS_MACOS) && !defined(__EWL_OS_ANDROID)
    #define __EWL_WINSERVER_XORG

#elif defined(__EWL_OS_WINDOWS)
    #define __EWL_WINSERVER_WINAPI

//elif defined ...
#endif