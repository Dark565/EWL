#include "../Xrandr_Impl.hpp"

inline XRRMonitorInfo* Xrandr::_XRRGetMonitors(Display* dsp,Window wnd,bool act,int* ret) {
    return XRRGetMonitors(dsp,wnd,act,ret);
}

inline void Xrandr::_XRRFreeMonitors(XRRMonitorInfo* mi) {
    XRRFreeMonitors(mi);
}

inline bool Xrandr::_load() {
    return true;
}

inline bool Xrandr::_unload() {
    return true;
}
