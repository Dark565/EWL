#pragma once

#include <string>
#include <stdint.h>

#include <QL/Definitions/Objects/type_arrays.hpp>
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

        virtual void onEvent(ql::Event) {}
        
        bool popEvent(ql::Event&);

        /* Creates a window */

        bool create(
            const std::string&,         //window's name
            const ql::array2ui&,        //window's size
            const ql::array2ui&,        //window's position
            const char = Style::all,    //window's flags
            const Window* = NULL        //window's parent
        );

        /* Closes a window */

        bool close();

        /* Changes window's position */

        bool setPosition(const ql::array2ui&);

        /* Changes window*s size */

        bool setSize(const ql::array2ui&);

        /* Gets cursor's size */

        ql::array2ui getCursorPosition();

        /* Gets window's position */

        ql::array2ui getWindowPosition();

        /* Gets window's size */

        ql::array2ui getWindowSize();

        /* Gets window's name */

        std::string getWindowName();

        /* Gets content of window */

        ql::Pixmap getWindowContent();

        /* Applies pixmap to the window on signed coordinates */

        bool applyPixmap(const ql::Pixmap&, const ql::array2ui&);

        /* Checks does window exist */

        bool isLegit();
        inline bool exist() {return isLegit();}

        inline Window(
            const std::string& name,        // window's name
            const ql::array2ui& size,       // window's size
            const ql::array2ui& position,   // window's position
            const char flags = Style::all,   // windows manager flags
            const Window* parent = NULL     // window's parent
        ) {create(name,size,position,flags,parent);}

        /* Default empty constructor */

        Window() = default;


    };

}