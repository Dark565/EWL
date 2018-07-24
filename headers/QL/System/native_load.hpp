#pragma once

#include <stdint.h>

namespace ql {
    enum tags {
        X11,
        Xrandr
    };

    namespace native {
        /*Loads the QL native module*/
        bool load(uint32_t tag);

        /*Unloads the module
         *Very dangerous operation*/
        bool unload(uint32_t tag);
    }
}