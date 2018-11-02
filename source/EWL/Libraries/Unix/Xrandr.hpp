#pragma once

#include <EWL/Definitions/libs.hpp>

#include <EWL/Definitions/func_typedefs.hpp>
#include <EWL-src/Libraries/dynamic_lib.hpp>

#include <X11/extensions/Xrandr.h>

struct Xrandr_Functions_Set {

    Xrandr::XRRFreeMonitors_p r_XRRFreeMonitors;
    Xrandr::XRRGetMonitors_p r_XRRGetMonitors;

};

bool G_Xrandr_lib_load();
bool G_Xrandr_lib_unload();

#define __EWL_LIB_XRANDR_PATH "libXrandr.so"

#if defined(__EWL_LIBRARY_LINK)
    #include "Xrandr/link.inl"
#elif defined(__EWL_LIBRARY_LOAD)
    #include "Xrandr/load.inl"
#endif

