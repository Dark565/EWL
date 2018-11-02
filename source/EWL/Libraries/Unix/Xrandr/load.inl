
#define _Xrandr_XRRGetMonitors\
    ewl::native::loadFunc<Xrandr::_XRRGetMonitors_p>(ewl::native::tags::Xrandr,"XRRGetMonitors")

#define _Xrandr_XRRFreeMonitors\
    ewl::native::loadFunc<Xrandr::_XRRFreeMonitors_p>(ewl::native::tags::Xrandr,"XRRFreeMonitrs")

#define _Xrandr_lib_load() \
    G_Xrandr_lib_load()

#define _Xrandr_lib_unload( ) \
    G_Xrandr_lib_unload()