#include <QL/Graphics/Display/display.hpp>

#include <QL/Definitions/protocols.hpp>

#include <QL/Definitions/int.hpp>

#if defined(__QL_WINSERVER_XORG)

    #include <QL-src/Libraries/Unix/X11-impl.inl>
    #include <QL-src/Libraries/Unix/Xrandr-impl.inl>

    #include "Display/impl_xorg.inl"
#elif defined(__QL_WINSERVER_WINAPI)
    #include "Display/impl_win32.inl"
//#elif defined ...
#endif

ql::Display::Display(bool open) {
    if(Display::init())
        if(open) Display::open(NULL);
    else
        throw std::string("Cannot init window protocol");
}

ql::Display::~Display() {
    close();
}
