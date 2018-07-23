#pragma once

#include <X11/Xlib.h>

namespace X11 {

    typedef Display*(*OpenDisplay_p)(const char*);
    typedef int(*CloseDisplay_p)(Display*);
    typedef Window(*CreateWindow_p)(
        Display*,
        Window,
        int,
        int,
        unsigned int,
        unsigned int,
        unsigned int,
        unsigned int,
        int,
        Visual*,
        unsigned long,
        XSetWindowAttributes*
    );
    typedef int(*StoreName_p)(Display*, Window, char* window_name);

    typedef Window Window;
    typedef Display Display;
    typedef Screen Screen;
    typedef XEvent XEvent;
    typedef Visual Visual;
    typedef XSetWindowAttributes XSetWindowAttributes;

}