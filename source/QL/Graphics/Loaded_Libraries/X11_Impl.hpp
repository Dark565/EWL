#pragma once

#include <QL/Definitions/libs.hpp>
#include "../../dynamic_lib.hpp"

#include <X11/Xlib.h>

#include <stdint.h>

namespace X11 {
    inline Display* OpenDisplay(const char*);
    inline int CloseDisplay(Display*);
    inline Window CreateWindow 
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
    inline int StoreName(Display*, Window, char*);
    inline char* GetAtomName(Display*,Atom);
    inline void Free(void*);
    inline Window DefaultRootWindow(Display*);
}

#if defined(__QL_LIBRARY_LINK)
    #include "Loaded_Libraries/X11/link.inl"
#elif defined(__QL_LIBRARY_LOAD)
    #include "Loaded_Libraries/X11/load.inl"
#endif