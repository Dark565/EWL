#pragma once

#include <QL/Definitions/libs.hpp>

#include <QL/Definitions/int.hpp>
#include <QL/Definitions/func_typedefs.hpp>
#include <QL-src/Libraries/dynamic_lib.hpp>

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

#define __QL_LIB_X11_PATH "libX11.so"

#if defined(__QL_LIBRARY_LINK)
    #include "X11/link.inl"
#elif defined(__QL_LIBRARY_LOAD)
    #include "X11/load.inl"
#endif