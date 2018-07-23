#pragma once

#include <QL/Graphics/Windows/window.hpp>
#include <QL/Definitions/servers.hpp>

#if defined(__QL_WINSERVER_XORG)
    #include "Windows/impl_xorg.inl"
#elif defined(__QL_WINSERVER_WINAPI)
    #include "Windows/impl_win32.inl"
#endif

