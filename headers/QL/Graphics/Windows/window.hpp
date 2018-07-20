#pragma once

#include <string>
#include <stdint.h>

#include <QL/Definitions/Objects/array.hpp>
#include <QL/Graphics/pixmap.hpp>
#include "event.hpp"

namespace ql {

    class Window {
        void* w_data; // private window's data
        char w_flags; // Class flags

        public:

        enum Style {
            all       = (0),            //All these things are on their places
            no_border = (1 << 0),       //Border goes out the window
            no_exit   = (1 << 1),       //Exit button similarly
            no_resize = (1 << 2),       //Resize button too
            no_fold   = (1 << 3),       //And lovely fold. What should we do with him? Fuck out
            nothing   = (1 << 4) - 1    //All window's manager addons are bad and they should never exist, lol
        };

        /* Function called on event */

        virtual void onEvent(ql::Event);
        
        bool popEvent(ql::Event&);

        /* Creates a window */

        bool create(const std::string&,             //window's name
                    const ql::Array<uint32_t,2>&,   //window's size
                    const ql::Array<uint32_t,2>&,   //window's position
                    char  flags = all);             //window's flags

        /* Closes a window */

        bool close();

        /* Changes window's position */

        bool setPosition(const ql::Array<uint32_t,2>&);

        /* Changes window*s size */

        bool setSize(const ql::Array<uint32_t,2>&);

        /* Gets cursor's size */

        ql::Array<uint32_t,2> getCursorPosition();

        /* Gets window's position */

        ql::Array<uint32_t,2> getWindowPosition();

        /* Gets window's size */

        ql::Array<uint32_t,2> getWindowSize();

        /* Gets window's name */

        std::string getWindowName();

        /* Gets content of window */

        ql::Pixmap getWindowContent();

        /* Checks does window exist */

        bool isLegit();

        Window(
            const std::string&,             // window's name
            const ql::Array<uint32_t,2>&,   // window's size
            const ql::Array<uint32_t,2>&,   // window's position
            char = all                      // window managerflags
        );

        Window() = default;


    };

}