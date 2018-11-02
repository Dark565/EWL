#pragma once

#include <EWL/Definitions/libs.hpp>

#include <EWL/Definitions/int.hpp>
#include <EWL/Definitions/func_typedefs.hpp>
#include <EWL-src/Libraries/dynamic_lib.hpp>

#include <X11/Xlib.h>

struct X11_Functions_Set {

    X11::OpenDisplay_p r_OpenDisplay;
    X11::CloseDisplay_p r_CloseDisplay;
    X11::CreateWindow_p r_CreateWindow;
    X11::StoreName_p r_StoreName;
    X11::GetAtomName_p r_GetAtomName;
    X11::Free_p r_Free;
    X11::DefaultRootWindow_p r_DefaultRootWindow;

};

bool G_X11_lib_load();
bool G_X11_lib_unload();

#define __EWL_LIB_X11_PATH "libX11.so"

#if defined(__EWL_LIBRARY_LINK)
    #include "X11/link.inl"
#elif defined(__EWL_LIBRARY_LOAD)
    #include "X11/load.inl"
#endif