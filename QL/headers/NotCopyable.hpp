#pragma once

/*Not copyable struct using to inheritance*/

namespace ql {

    struct NotCopyable {
        NotCopyable() = default;
    protected:
        NotCopyable(const NotCopyable&) = delete;
        NotCopyable& operator =(const NotCopyable&) = delete;
    };

}