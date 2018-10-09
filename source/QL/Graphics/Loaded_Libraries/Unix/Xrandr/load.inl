#include <QL/Definitions/func_typedefs.hpp>

#include "../Xrandr_Impl.hpp"

inline XRRMonitorInfo* Xrandr::_XRRGetMonitors(Display* dsp,Window wnd,bool act,int* ret) {
    return ql::native::loadFunc<Xrandr::_XRRGetMonitors_p>(ql::native::tags::Xrandr,"XRRGetMonitors")(dsp,wnd,act,ret);
}

inline void Xrandr::_XRRFreeMonitors(XRRMonitorInfo* mi) {
    ql::native::loadFunc<Xrandr::_XRRFreeMonitors_p>(ql::native::tags::Xrandr,"XRRFreeMonitors")(mi);
}

inline bool Xrandr::_load() {
    return ql::native::loadLibrary(ql::native::tags::Xrandr,__QL_LIB_XRANDR_PATH);
}

inline bool Xrandr::_unload() {
    return ql::native::unloadLibrary(ql::native::tags::Xrandr);
}