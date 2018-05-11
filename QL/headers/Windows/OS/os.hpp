#pragma once

#include "../../Definitions/defs.hpp"

#if defined __QL_UNIX
    #include "Unix/Xorg/types.hpp"
#elif defined __QL_WINDOWS
    #include "WIN32/types.hpp"
#elif defined __QL_APPLE
    //
#elif defined __QL_ANDROID
    //
#endif