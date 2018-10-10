#include <QL/Definitions/func_typedefs.hpp>

#include "../Xrandr_Impl.hpp"


#define _Xrandr_XRRGetMonitors(dsp,wnd,act,ret) \
    ql::native::loadFunc<Xrandr::_XRRGetMonitors_p>(ql::native::tags::Xrandr,"XRRGetMonitors")(dsp,wnd,act,ret)

#define _Xrandr_XRRFreeMonitors(mi) \
    ql::native::loadFunc<Xrandr::_XRRFreeMonitors_p>(ql::native::tags::Xrandr,"XRRFreeMonitors")(mi)

#define _Xrandr_lib_load() \
    ql::native::loadLibrary(ql::native::tags::Xrandr,__QL_LIB_XRANDR_PATH)

#define _Xrandr_lib_unload() \
    ql::native::unloadLibrary(ql::native::tags::Xrandr)