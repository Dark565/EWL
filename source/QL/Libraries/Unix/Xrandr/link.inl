#include "../Xrandr_Impl.hpp"


#define _Xrandr_XRRGetMonitors(dsp,wnd,act,ret) \
    XRRGetMonitors(dsp,wnd,act,ret)

#define _Xrandr_XRRFreeMonitors(mi) \
    XRRFreeMonitors(mi)

#define _Xrandr_lib_load() \
    1

#define _Xrandr_lib_unload() \
    1
