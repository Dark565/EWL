
#define _Xrandr_XRRGetMonitors\
    ql::native::loadFunc<Xrandr::_XRRGetMonitors_p>(ql::native::tags::Xrandr,"XRRGetMonitors")

#define _Xrandr_XRRFreeMonitors\
    ql::native::loadFunc<Xrandr::_XRRFreeMonitors_p>(ql::native::tags::Xrandr,"XRRFreeMonitrs")

#define _Xrandr_lib_load() \
    G_Xrandr_lib_load()

#define _Xrandr_lib_unload( ) \
    G_Xrandr_lib_unload()