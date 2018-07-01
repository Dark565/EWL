#include <QL/Graphics/Display/display.hpp>

#include <QL/Graphics/WinServer/servers.hpp>

#include <cstdint>

#if defined(__QL_WINSERVER_XORG)
    #include "Xorg/impl.inl"
#elif defined(__QL_WINSERVER_WINAPI)
    #include "Win32/impl.inl"
//#elif defined ...
#endif

ql::Display::Display(bool open) {
    if(open) ql::Display::open(NULL);
}

ql::Display::~Display() {
    close();
}