#include <QL/Definitions/func_typedefs.hpp>

inline Display* X11::_XOpenDisplay(const char* s) {
    return ql::native::loadFunc<X11::OpenDisplay_p>(ql::native::tags::X11,"XOpenDisplay")(s);
}

inline int X11::_XCloseDisplay(Display* d) {
    return ql::native::loadFunc<X11::CloseDisplay_p>(ql::native::tags::X11,"XCloseDisplay")(d);
}

inline Window X11::_XCreateWindow
                    (
                        Display* dsp,
                        Window parent,
                        ql::int32_t x, ql::int32_t y,           
                        ql::uint32_t width, ql::uint32_t height,         
                        ql::uint32_t border_width,                   
                        ql::int32_t depth,                    
                        ql::uint32_t c_class,                   
                        Visual* visual,                    
                        ql::uint32_t valuemask,                   
                        XSetWindowAttributes* attributes      
                    )
{
    return ql::native::loadFunc<X11::CreateWindow_p>(ql::native::tags::X11,"XCreateWindow")
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

inline int X11::_XStoreName(Display* dsp, Window wnd, char* n) {
    return ql::native::loadFunc<X11::StoreName_p>(ql::native::tags::X11,"XStoreName")(dsp,wnd,n);
}

inline char* X11::_XGetAtomName(Display* dsp, Atom a) {
    return ql::native::loadFunc<X11::GetAtomName_p>(ql::native::tags::X11,"XGetAtomName")(dsp,a);
}

inline int X11::_XFree(void* d) {
    return ql::native::loadFunc<X11::Free_p>(ql::native::tags::X11,"XFree")(d);
}

inline Window X11::_XDefaultRootWindow(Display* d) {
    return ql::native::loadFunc<X11::DefaultRootWindow_p>(ql::native::tags::X11,"XDefaultRootWindow")(d);
}

inline bool X11::_load() {
    return ql::native::loadLibrary(ql::native::tags::X11,__QL_LIB_X11_PATH);
}

inline bool X11::_unload() {
    return ql::native::unloadLibrary(ql::native::tags::X11);
}