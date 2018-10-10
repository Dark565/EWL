#pragma once

#include <QL/Definitions/libs.hpp>
#include <QL-src/Libraries/dynamic_lib.hpp>

#include <X11/Xlib.h>

#include <QL/Definitions/int.hpp>

#define __QL_LIB_X11_PATH "libX11.so"

#if defined(__QL_LIBRARY_LINK)
    #include "X11/link.inl"
#elif defined(__QL_LIBRARY_LOAD)
    #include "X11/load.inl"
#endif