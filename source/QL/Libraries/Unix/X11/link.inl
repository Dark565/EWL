#define _X11_OpenDisplay(s) \
    XOpenDisplay(s)

#define _X11_CloseDisplay(d) \
    XCloseDisplay(d)

#define _X11_CreateWindow(dsp,parent,x,y,width,height,border_width,depth,c_class,visual,valuemask,attributes) \
    XCreateWindow\
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
    XStoreName(dsp,wnd,n)

#define _X11_GetAtomName(dsp,a)\
    XGetAtomName(dsp,a)

#define _X11_Free(d)\
    XFree(d)

#define _X11_DefaultRootWindow(d)\
    XDefaultRootWindow(d)

#define _X11_lib_load()\
    1

#define _X11_lib_unload()\
    1