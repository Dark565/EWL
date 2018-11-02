#pragma once

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <EWL/Definitions/int.hpp>

namespace X11 {

    typedef Display*(*OpenDisplay_p)(const char*);
    typedef int(*CloseDisplay_p)(Display*);
    typedef Window(*CreateWindow_p)(
        Display*,
        Window,
        ewl::int32_t, ewl::int32_t,
        ewl::uint32_t, ewl::uint32_t,
        ewl::uint32_t,
        ewl::int32_t,
        ewl::uint32_t,
        Visual*,
        ewl::uint32_t,
        XSetWindowAttributes*
    );
    typedef int(*StoreName_p)(Display*, Window, char* window_name);
    typedef char*(*GetAtomName_p)(Display*,Atom);
    typedef int(*Free_p)(void*);
    typedef Window(*DefaultRootWindow_p)(Display*);

    typedef Display Display;
    typedef Window Window;
    typedef Atom Atom;

}

namespace Xrandr {

    typedef XRRMonitorInfo*(*XRRGetMonitors_p)(Display*,Window,bool,int*);
    typedef void(*XRRFreeMonitors_p)(XRRMonitorInfo*);

}