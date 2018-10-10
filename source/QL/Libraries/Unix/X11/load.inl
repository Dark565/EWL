#include <QL/Definitions/func_typedefs.hpp>

#define _X11_OpenDisplay(s) \
    ql::native::loadFunc<X11::OpenDisplay_p>(ql::native::tags::X11,"XOpenDisplay")(s)

#define _X11_CloseDisplay(d) \
    ql::native::loadFunc<X11::CloseDisplay_p>(ql::native::tags::X11,"XCloseDisplay")(d)

#define _X11_CreateWindow(dsp,parent,x,y,width,height,border_width,depth,c_class,visual,valuemask,attributes) \
    ql::native::loadFunc<X11::CreateWindow_p>(ql::native::tags::X11,"XCreateWindow")\
            (\
                dsp,\
                parent,\
                x,y,\
                width, height,\
                border_width,\
                depth,\
                c_class,\
                visual,\
                valuemask,\
                attributes\
            )

#define _X11_StoreName(dsp,wnd,n)\
    ql::native::loadFunc<X11::StoreName_p>(ql::native::tags::X11,"XStoreName")(dsp,wnd,n)

#define _X11_GetAtomName(dsp,a)\
    ql::native::loadFunc<X11::GetAtomName_p>(ql::native::tags::X11,"XGetAtomName")(dsp,a)

#define _X11_Free(d)\
    ql::native::loadFunc<X11::Free_p>(ql::native::tags::X11,"XFree")(d)

#define _X11_DefaultRootWindow(d)\
    ql::native::loadFunc<X11::DefaultRootWindow_p>(ql::native::tags::X11,"XDefaultRootWindow")(d)

#define _X11_lib_load()\
    ql::native::loadLibrary(ql::native::tags::X11,__QL_LIB_X11_PATH)

#define _X11_lib_unload()\
    ql::native::unloadLibrary(ql::native::tags::X11)