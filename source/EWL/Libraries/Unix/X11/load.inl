
#define _X11_OpenDisplay\
    ewl::native::loadFunc<X11::OpenDisplay_p>(ewl::native::tags::X11,"XOpenDisplay")

#define _X11_CloseDisplay\
    ewl::native::loadFunc<X11::CloseDisplay_p>(ewl::native::tags::X11,"XCloseDisplay")

#define _X11_CreateWindow\
    ewl::native::loadFunc<X11::CreateWindow_p>(ewl::native::tags::X11,"XCreateWindow")

#define _X11_StoreName\
    ewl::native::loadFunc<X11::StoreName_p>(ewl::native::tags::X11,"XStoreName")

#define _X11_GetAtomName\
    ewl::native::loadFunc<X11::GetAtomName_p>(ewl::native::tags::X11,"XGetAtomName")

#define _X11_Free\
    ewl::native::loadFunc<X11::Free_p>(ewl::native::tags::X11,"XFree")

#define _X11_DefaultRootWindow\
    ewl::native::loadFunc<X11::DefaultRootWindow_p>(ewl::native::tags::X11,"XDefaultRootWindow")

#define _X11_lib_load()\
    G_X11_lib_load()

#define _X11_lib_unload()\
    G_X11_lib_unload()