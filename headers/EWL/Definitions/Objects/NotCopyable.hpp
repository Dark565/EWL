#pragma once

/*Not copyable struct using to inheritance*/

namespace ewl {

    struct NotCopyable {
    protected:
        NotCopyable() = default;
        NotCopyable(const NotCopyable&) = delete;
        NotCopyable& operator =(const NotCopyable&) = delete;
    };

}