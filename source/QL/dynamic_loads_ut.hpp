#pragma once

#include "Graphics/Loaded_Libraries/X11_Impl.hpp"
#include "Graphics/Loaded_Libraries/Xrandr_Impl.hpp"

#if defined(__QL_LIBRARY_LINK)
    #undef __QL_LIBRARY_LINK
#endif

#define __QL_LIBRARY_LOAD

namespace native {
    namespace M0 = X11;
    namespace M1 = Xrandr;
}