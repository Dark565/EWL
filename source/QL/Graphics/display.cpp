#include <QL/Graphics/Display/display.hpp>

#include <QL/Graphics/Display/controller.hpp>

#include <cstdint>

#if defined(__QL_WINSERVER_XORG)
    #include "Display/impl_xorg.inl"
#elif defined(__QL_WINSERVER_WINAPI)
    #include "Display/impl_win32.inl"
//#elif defined ...
#endif

ql::Display::Display(bool open) {
    if(open) ql::Display::open(NULL);
}

ql::Display::~Display() {
    close();
}