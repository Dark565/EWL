#pragma once

#include <QL/Definitions/libs.hpp>

#include <QL/Definitions/func_typedefs.hpp>
#include <QL-src/Libraries/dynamic_lib.hpp>

#include <X11/extensions/Xrandr.h>

struct Xrandr_Functions_Set {

    Xrandr::XRRFreeMonitors_p r_XRRFreeMonitors;
    Xrandr::XRRGetMonitors_p r_XRRGetMonitors;

};

bool G_Xrandr_lib_load();
bool G_Xrandr_lib_unload();

#define __QL_LIB_XRANDR_PATH "libXrandr.so"

#if defined(__QL_LIBRARY_LINK)
    #include "Xrandr/link.inl"
#elif defined(__QL_LIBRARY_LOAD)
    #include "Xrandr/load.inl"
#endif

