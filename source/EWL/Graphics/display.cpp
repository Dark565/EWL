#include <EWL/Graphics/Display/display.hpp>

#include <EWL/Definitions/protocols.hpp>

#include <EWL/Definitions/int.hpp>

#if defined(__EWL_WINSERVER_XORG)

    #include <EWL-src/Libraries/Unix/X11-impl.inl>
    #include <EWL-src/Libraries/Unix/Xrandr-impl.inl>

    #include "Display/impl_xorg.inl"
#elif defined(__EWL_WINSERVER_WINAPI)
    #include "Display/impl_win32.inl"
//#elif defined ...
#endif

ewl::Display::Display(bool open) {
    if(Display::init())
        if(open) Display::open(NULL);
    else
        throw std::string("Cannot init window protocol");
}

ewl::Display::~Display() {
    close();
}
