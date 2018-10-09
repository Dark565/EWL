#include "../X11_Impl.hpp"

inline Display* X11::_XOpenDisplay(const char* d) {
    return XOpenDisplay(d);
}

inline int X11::_XCloseDisplay(Display* d) {
    return XCloseDisplay(d);
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
    return XCreateWindow
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
    return XStoreName(dsp,wnd,n);
}

inline char* X11::_XGetAtomName(Display* dsp, Atom a) {
    return XGetAtomName(dsp,a);
}

inline int X11::_XFree(void* d) {
    return XFree(d);
}

inline Window X11::_XDefaultRootWindow(Display*d ) {
    return XDefaultRootWindow(d);
}

inline bool X11::_load() {
    return true;
}

inline bool X11::_unload() {
    return true;
}