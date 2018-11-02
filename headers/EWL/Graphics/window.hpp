#pragma once

#include <string>
#include <EWL/Definitions/int.hpp>

#include <EWL/Definitions/Objects/type_arrays.hpp>
#include <EWL/Graphics/pixmap.hpp>

namespace ewl {

    class Window {
        void* w_data; // private window's data
        char w_flags; // Class flags

        public:

        enum Style {
            all       = (1),            //All these things are on their places
            no_border = (1 << 0),       //Border goes out of the window
            no_exit   = (1 << 1),       //Exit button similarly
            no_resize = (1 << 2),       //Resize button too
            no_fold   = (1 << 3),       //And lovely fold. What shall we do with him? Fuck out
            nothing   = (1 << 4) - 1    //All window manager's addons are bad and they should never exist, lol
        };

        /* Function called on event */

        //virtual void onEvent(ewl::Event) {}
        
        //bool popEvent(ewl::Event&);

        /* Creates a window */

        bool create(
            const std::string&,         //window's name
            const ewl::array2ui&,        //window's size
            const ewl::array2ui&,        //window's position
            const char = Style::all,    //window's flags
            const Window* = NULL        //window's parent
        );

        /* Closes a window */

        bool close();

        /* Changes window's position */

        bool setPosition(const ewl::array2ui&);

        /* Changes window*s size */

        bool setSize(const ewl::array2ui&);

        /* Gets cursor's size */

        ewl::array2ui getCursorPosition();

        /* Gets window's position */

        ewl::array2ui getWindowPosition();

        /* Gets window's size */

        ewl::array2ui getWindowSize();

        /* Gets window's name */

        std::string getWindowName();

        /* Gets content of window */

        ewl::Pixmap getWindowContent();

        /* Applies pixmap to the window on signed coordinates */

        bool applyPixmap(const ewl::Pixmap&, const ewl::array2ui&);

        /* Checks does window exist */

        bool isLegit();
        inline bool exist() {return isLegit();}

        inline Window(
            const std::string& name,        // window's name
            const ewl::array2ui& size,       // window's size
            const ewl::array2ui& position,   // window's position
            const char flags = Style::all,  // windows manager flags
            const Window* parent = NULL     // window's parent
        ) {create(name,size,position,flags,parent);}

        /* Default empty constructor */

        Window() = default;


    };

}