#include <X11/extensions/Xrandr.h>
#include <X11/Xlib.h>

#include <QL/Graphics/Display/monitors.hpp>
#include "../Loaded_Libraries/Xrandr_Impl.hpp"
#include "../Loaded_Libraries/X11_Impl.hpp"

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

        char* n = X11::GetAtomName(d, mi.name);
        ret.name = n;

        XFree(n);

        return ret;
    }
}

bool ql::Display::open(const char* name) {
    close();

    Xdsp = X11::OpenDisplay(name);
    
    return Xdsp;
}

bool ql::Display::isOpen() {
    return (Xdsp != NULL);
}

int ql::Display::getMonitorCount() {
    if(!isOpen()) return -1;

    int ret;
    XRRFreeMonitors(Xrandr::_XRRGetMonitors(Xdsp, X11::_DefaultRootWindow(Xdsp), 1, &ret));
    return ret;
}

bool ql::Display::getMonitor(int index, ql::Monitor& m) {
    if(!isOpen()) return false;

    int size;
    XRRMonitorInfo* mi = Xrandr::_XRRGetMonitors(Xdsp, X11::_DefaultRootWindow(Xdsp), 1, &size);

    bool r = false;

    if(index < size) {
        m = priv::copyFromXRRMonitorInfo(Xdsp,mi[index]);

        r = true;
    }

    Xrandr::_XRRFreeMonitors(mi);

    return r;
}

std::vector<ql::Monitor> ql::Display::getMonitors() {
    std::vector<ql::Monitor> ret;
    if(isOpen()) {

        int size;
        XRRMonitorInfo* mi = Xrandr::_XRRGetMonitors(Xdsp, X11::_DefaultRootWindow(Xdsp), 1, &size);

        for(uint32_t i = 0; i < size; i++) {
            ret.push_back(priv::copyFromXRRMonitorInfo(Xdsp,mi[i]));
        }

        Xrandr::_XRRFreeMonitors(mi);

    }
    return ret;
}

bool ql::Display::close() {
    if(isOpen()) {
        X11::CloseDisplay(Xdsp);
        Xdsp = NULL;
    }
}

bool ql::Display::init() {
    return X11::load();
}