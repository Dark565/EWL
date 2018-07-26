#pragma once

#include <QL/Definitions/libs.hpp>
#include "../../dynamic_lib.hpp"

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#define __QL_LIB_XRANDR_PATH "libXrandr.so"

namespace Xrandr {
    inline XRRMonitorInfo* _XRRGetMonitors(Display*,Window,bool,int*);
    inline void _XRRFreeMonitors(XRRMonitorInfo*);

    inline bool _load();
    inline bool _unload();
}

#if defined(__QL_LIBRARY_LINK)
    #include "Xrandr/link.inl"
#elif defined(__QL_LIBRARY_LOAD)
    #include "Xrandr/load.inl"
#endif

