#include <QL/Definitions/func_typedefs.hpp>
#include "../../dynlibs_tags.hpp"

inline Display* X11::OpenDisplay(const char* s) {
    return ql::dynamicLib::loadFunc<X11::OpenDisplay_p>(ql::tags::X11,"XOpenDisplay")(s);
}

inline int X11::CloseDisplay(Display* d) {
    return ql::dynamicLib::loadFunc<X11::CloseDisplay_p>(ql::tags::X11,"XCloseDisplay")(d);
}

inline Window X11::CreateWindow
                    (
                        Display* dsp,
                        Window parent,
                        int32_t x, int32_t y,           
                        uint32_t width, uint32_t height,         
                        uint32_t border_width,                   
                        int32_t depth,                    
                        uint32_t c_class,                   
                        Visual* visual,                    
                        uint32_t valuemask,                   
                        XSetWindowAttributes* attributes      
                    )
{
    return ql::dynamicLib::loadFunc<X11::CreateWindow_p>(ql::tags::X11,"XCreateWindow")
            (
                dsp,
                parent,
                x,y,
                width, height,
                border_width,
                depth,
                c_class,
                visual,
                valuemask,
                attributes
            );
}

inline int X11::StoreName(Display* dsp, Window wnd, char* n) {
    return ql::dynamicLib::loadFunc<X11::StoreName_p>(ql::tags::X11,"XStoreName")(dsp,wnd,n);
}

inline char* X11::GetAtomName(Display* dsp, Atom a) {
    return ql::dynamicLib::loadFunc<X11::GetAtomName_p>(ql::tags::X11,"XGetAtomName")(dsp,a);
}

inline void X11::Free(void* d) {
    ql::dynamicLib::loadFunc<X11::Free_p>(ql::tags::X11,"XFree")(d);
}

inline Window X11::DefaultRootWindow(Display* d) {
    return ql::dynamicLib::loadFunc<X11::DefaultRootWindow_p>(ql::tags::X11,"XDefaultRootWindow")(d);
}