#pragma once

#include <QL/Graphics/Windows/window.hpp>
#include <QL/Definitions/protocols.hpp>

namespace priv  {

}

#if defined(__QL_WINSERVER_XORG)
    #include "Window/impl_xorg.inl"
#elif defined(__QL_WINSERVER_WINAPI)
    #include "Window/impl_win32.inl"
#endif

