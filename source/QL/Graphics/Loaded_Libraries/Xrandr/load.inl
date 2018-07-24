#include <QL/Definitions/func_typedefs.hpp>

#include <QL/System/native_load.hpp>

#include "../Xrandr_Impl.hpp"

inline XRRMonitorInfo* Xrandr::_XRRGetMonitors(Display* dsp,Window wnd,bool act,int* ret) {
    return ql::native::loadFunc<Xrandr::_XRRGetMonitors_p>(ql::tags::Xrandr,"XRRGetMonitors")(dsp,wnd,act,ret);
}

inline void Xrandr::_XRRFreeMonitors(XRRMonitorInfo* mi) {
    ql::native::loadFunc<Xrandr::_XRRFreeMonitors_p>(ql::tags::Xrandr,"XRRFreeMonitors")(mi);
}

inline bool Xrandr::load() {
    return ql::native::loadLibrary(ql::tags::Xrandr,__QL_LIB_XRANDR_PATH);
}

inline bool Xrandr::unload() {
    return ql::native::unloadLibrary(ql::tags::Xrandr);
}