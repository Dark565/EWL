#pragma once

#include <QL/System/library.hpp>
#include <QL/Definitions/compiller.hpp>

#include <X11/Xlib.h>

#define __QL_X11_SO_PATH "libX11.so"

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

    bool load();
    ql::Library* getLibrary();
}