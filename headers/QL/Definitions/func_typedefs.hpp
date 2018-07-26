#pragma once

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <stdint.h>

namespace X11 {

    typedef Display*(*OpenDisplay_p)(const char*);
    typedef int(*CloseDisplay_p)(Display*);
    typedef Window(*CreateWindow_p)(
        Display*,
        Window,
        int32_t, int32_t,
        uint32_t, uint32_t,
        uint32_t,
        int32_t,
        uint32_t,
        Visual*,
        uint32_t,
        XSetWindowAttributes*
    );
    typedef int(*StoreName_p)(Display*, Window, char* window_name);
    typedef char*(*GetAtomName_p)(Display*,Atom);
    typedef int(*Free_p)(void*);
    typedef Window(*DefaultRootWindow_p)(Display*);

}

namespace Xrandr {

    typedef XRRMonitorInfo*(*_XRRGetMonitors_p)(Display*,Window,bool,int*);
    typedef void(*_XRRFreeMonitors_p)(XRRMonitorInfo*);

}