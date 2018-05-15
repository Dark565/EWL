#pragma once

namespace ql {
    namespace mouse {
        enum class Button : char {
            left,
            right,
            middle
        };

        enum class Press : char {
            off,
            on,
            double_click
        };
    };
}