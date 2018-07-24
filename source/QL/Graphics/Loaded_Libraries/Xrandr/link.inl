inline XRRMonitorInfo* Xrandr::_XRRGetMonitors(Display* dsp,Window wnd,bool act,int* ret) {
    return XRRGetMonitors(dsp,wnd,act,ret);
}

inline void Xrandr::_XRRFreeMonitors(XRRMonitorInfo* mi) {
    XRRFreeMonitors(mi);
}

