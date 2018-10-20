
#define _X11_OpenDisplay\
    ql::native::loadFunc<X11::OpenDisplay_p>(ql::native::tags::X11,"XOpenDisplay")

#define _X11_CloseDisplay\
    ql::native::loadFunc<X11::CloseDisplay_p>(ql::native::tags::X11,"XCloseDisplay")

#define _X11_CreateWindow\
    ql::native::loadFunc<X11::CreateWindow_p>(ql::native::tags::X11,"XCreateWindow")

#define _X11_StoreName\
    ql::native::loadFunc<X11::StoreName_p>(ql::native::tags::X11,"XStoreName")

#define _X11_GetAtomName\
    ql::native::loadFunc<X11::GetAtomName_p>(ql::native::tags::X11,"XGetAtomName")

#define _X11_Free\
    ql::native::loadFunc<X11::Free_p>(ql::native::tags::X11,"XFree")

#define _X11_DefaultRootWindow\
    ql::native::loadFunc<X11::DefaultRootWindow_p>(ql::native::tags::X11,"XDefaultRootWindow")

#define _X11_lib_load()\
    G_X11_lib_load()

#define _X11_lib_unload()\
    G_X11_lib_unload()