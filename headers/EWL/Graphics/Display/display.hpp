#pragma once

#include <EWL/Definitions/Objects/NotCopyable.hpp>
#include <EWL/Definitions/protocols.hpp>
#include "monitors.hpp"

#include <vector>

#if defined(__EWL_WINSERVER_XORG)
    #include <X11/Xlib.h>

#elif defined(__EWL_WINSERVER_WINAPI)
    #include <winapi.h>

//#elif defined ...

#endif

namespace ewl {

    class Display : NotCopyable {

    protected:

        #if defined(__EWL_WINSERVER_XORG)
            _XDisplay* Xdsp = NULL;
        #endif

    public:

        #if defined(__EWL_WINSERVER_XORG)
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

        static bool init();


    };
}