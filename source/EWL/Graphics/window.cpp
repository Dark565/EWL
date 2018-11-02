#include <EWL/Definitions/protocols.hpp>
#include <EWL/Graphics/window.hpp>

#include <stdlib.h>

#if defined(__EWL_WINSERVER_XORG)
    #include "Window/impl_xorg.inl"
#elif defined(__EWL_WINSERVER_WINAPI)
    #include "Window/impl_win32.inl"
#endif
