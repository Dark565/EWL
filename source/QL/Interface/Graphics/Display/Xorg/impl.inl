#include <QL/Graphics/Display/display.hpp>
#include <X11/extensions/Xrandr.h>

#include <QL/Graphics/Display/monitors.hpp>
#include <vector>

namespace priv {
    ql::Monitor copyFromXRRMonitorInfo(_XDisplay* d, const XRRMonitorInfo& mi) {
        ql::Monitor ret;
        
        ret.height = mi.height;
        ret.width = mi.width;
        ret.width_mm = mi.mwidth;
        ret.height_mm = mi.mwidth;
        ret.x = mi.x;
        ret.y = mi.y;

        ret.name = XGetAtomName(d, mi.name);

        return ret;
    }
}

bool ql::Display::open(const char* name) {
    close();

    Xdsp = XOpenDisplay(name);
    
    return Xdsp;
}

bool ql::Display::isOpen() {
    return (Xdsp != NULL);
}

int ql::Display::getMonitorCount() {
    if(!isOpen()) return -1;

    int ret;
    XRRFreeMonitors(XRRGetMonitors(Xdsp, XDefaultRootWindow(Xdsp), 1, &ret));
    return ret;
}

bool ql::Display::getMonitor(int index, ql::Monitor& m) {
    if(!isOpen()) return false;

    int size;
    XRRMonitorInfo* mi = XRRGetMonitors(Xdsp, XDefaultRootWindow(Xdsp), 1, &size);

    bool r = false;

    if(index < size) {
        m = priv::copyFromXRRMonitorInfo(Xdsp,mi[index]);

        r = true;
    }

    XRRFreeMonitors(mi);

    return r;
}

std::vector<ql::Monitor> ql::Display::getMonitors() {
    std::vector<ql::Monitor> ret;
    if(isOpen()) {

        int size;
        XRRMonitorInfo* mi = XRRGetMonitors(Xdsp, XDefaultRootWindow(Xdsp), 1, &size);

        for(uint32_t i = 0; i < size; i++) {
            ret.push_back(priv::copyFromXRRMonitorInfo(Xdsp,mi[i]));
        }

        XRRFreeMonitors(mi);

    }
    return ret;
}

bool ql::Display::close() {
    if(isOpen()) {
        XCloseDisplay(Xdsp);
    }
}