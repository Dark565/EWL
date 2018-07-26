#pragma once

#include <QL/Definitions/libs.hpp>
#include "../../dynamic_lib.hpp"

#include <X11/Xlib.h>

#include <stdint.h>

#define __QL_LIB_X11_PATH "libX11.so"

namespace X11 {
    inline Display* _XOpenDisplay(const char*);
    inline int _XCloseDisplay(Display*);
    inline Window _XCreateWindow 
                    (
                        Display*,                   //X11 connection data pointer
                        Window,                     //Parent
                        int32_t, int32_t,           //x, y
                        uint32_t, uint32_t,         //width, height
                        uint32_t,                   //border width
                        int32_t,                    //depth
                        uint32_t,                   //class
                        Visual*,                    //visual
                        uint32_t,                   //value mask
                        XSetWindowAttributes*       //attributes
                    );
    inline int _XStoreName(Display*, Window, char*);
    inline char* _XGetAtomName(Display*,Atom);
    inline int _XFree(void*);
    inline Window _XDefaultRootWindow(Display*);

    inline bool _load();
    inline bool _unload();
}

#if defined(__QL_LIBRARY_LINK)
    #include "X11/link.inl"
#elif defined(__QL_LIBRARY_LOAD)
    #include "X11/load.inl"
#endif