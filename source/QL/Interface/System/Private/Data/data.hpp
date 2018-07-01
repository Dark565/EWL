#pragma once

namespace ql {
    namespace mystery {
        struct data {
            int argc;
            char** argv;
            int used_WM;
        };

        data* getMysteryDataPtr();
    }
}