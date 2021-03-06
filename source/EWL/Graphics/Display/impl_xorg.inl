#include <X11/extensions/Xrandr.h>
#include <X11/Xlib.h>

#include <EWL/Graphics/Display/monitors.hpp>

#include <EWL-src/Libraries/Unix/Xrandr.hpp>
#include <EWL-src/Libraries/Unix/X11.hpp>

#include <vector>

namespace priv {
    ewl::Monitor copyFromXRRMonitorInfo(_XDisplay* d, const XRRMonitorInfo& mi) {
        ewl::Monitor ret;
        
        ret.height = mi.height;
        ret.width = mi.width;
        ret.width_mm = mi.mwidth;
        ret.height_mm = mi.mwidth;
        ret.x = mi.x;
        ret.y = mi.y;

        char* n = _X11_GetAtomName(d, mi.name);
        ret.name = n;

        _X11_Free(n);

        return ret;
    }
}

bool ewl::Display::open(const char* name) {
    close();

    Xdsp = _X11_OpenDisplay(name);
    
    return Xdsp;
}

bool ewl::Display::isOpen() {
    return Xdsp != NULL;
}

int ewl::Display::getMonitorCount() {
    if(!isOpen()) return -1;

    int ret;
    _Xrandr_XRRFreeMonitors(_Xrandr_XRRGetMonitors(Xdsp, _X11_DefaultRootWindow(Xdsp), 1, &ret));
    return ret;
}

bool ewl::Display::getMonitor(int index, ewl::Monitor& m) {
    if(!isOpen()) return false;

    int size;
    XRRMonitorInfo* mi = _Xrandr_XRRGetMonitors(Xdsp, _X11_DefaultRootWindow(Xdsp), 1, &size);

    bool r = false;

    if(index < size) {
        m = priv::copyFromXRRMonitorInfo(Xdsp,mi[index]);

        r = true;
    }

    _Xrandr_XRRFreeMonitors(mi);

    return r;
}

std::vector<ewl::Monitor> ewl::Display::getMonitors() {
    std::vector<ewl::Monitor> ret;
    if(isOpen()) {

        int size;
        XRRMonitorInfo* mi = _Xrandr_XRRGetMonitors(Xdsp, _X11_DefaultRootWindow(Xdsp), 1, &size);

        for(ewl::uint32_t i = 0; i < size; i++) {
            ret.push_back(priv::copyFromXRRMonitorInfo(Xdsp,mi[i]));
        }

        _Xrandr_XRRFreeMonitors(mi);

    }
    return ret;
}

bool ewl::Display::close() {
    if(isOpen()) {
        _X11_CloseDisplay(Xdsp);
        Xdsp = NULL;
        return true;
    }
    return false;
}

bool ewl::Display::init() {
    return _X11_lib_load() && _Xrandr_lib_load();
}