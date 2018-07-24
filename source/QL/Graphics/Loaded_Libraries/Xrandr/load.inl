#include <QL/Definitions/func_typedefs.hpp>
#include "../../dynlibs_tags.hpp"

inline XRRMonitorInfo* Xrandr::_XRRGetMonitors(Display* dsp,Window wnd,bool act,int* ret) {
    return ql::dynamicLib::loadFunc<Xrandr::_XRRGetMonitors_p>(ql::tags::Xrandr,"XRRGetMonitors")(dsp,wnd,act,ret);
}

inline void Xrandr::_XRRFreeMonitors(XRRMonitorInfo* mi) {
    ql::dynamicLib::loadFunc<Xrandr::_XRRFreeMonitors_p>(ql::tags::Xrandr,"XRRFreeMonitors")(mi);
}