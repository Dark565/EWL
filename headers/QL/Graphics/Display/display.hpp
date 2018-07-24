#pragma once

#include <QL/Definitions/NotCopyable.hpp>
#include <QL/Graphics/Windows/window.hpp>
#include <QL/Definitions/protocols.hpp>
#include "monitors.hpp"

#include <vector>

#if defined(__QL_WINSERVER_XORG)
    #include <X11/Xlib.h>

#elif defined(__QL_WINSERVER_WINAPI)
    #include <winapi.h>

//#elif defined ...

#endif

namespace ql {

    class Display : NotCopyable {

    protected:

        #if defined(__QL_WINSERVER_XORG)
            _XDisplay* Xdsp = NULL;
        #endif

        void init();

    public:

        #if defined(__QL_WINSERVER_XORG)
            bool open(const char* name);
        #endif

        bool close();

        bool isOpen();

        int getMonitorCount();

        bool getMonitor(int index, Monitor& m);

        std::vector<Monitor> getMonitors();

        Display(bool open = true);
        ~Display();

        friend class Window;


    };
}