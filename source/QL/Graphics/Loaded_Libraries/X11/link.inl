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
            )
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