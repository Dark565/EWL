#pragma once


#include <QL/Definitions/libs.hpp>
#include "../../dynamic_lib.hpp"

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

namespace Xrandr {
    inline XRRMonitorInfo* _XRRGetMonitors(Display*,Window,bool,int*);
    inline void _XRRFreeMonitors(XRRMonitorInfo*);
}

#if defined(__QL_LIBRARY_LINK)
    #include "Xrandr/link.inl"
#elif defined(__QL_LIBRARY_LOAD)
    #include "Xrandr/load.inl"
#endif

