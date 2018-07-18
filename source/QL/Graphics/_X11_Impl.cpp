#include "_X11_Impl.hpp"

static ql::Library X11_Lib;

ql::Library* X11::getLibrary() {
    return &X11_Lib;
}

bool X11::load() {
    return X11_Lib.load(__QL_X11_SO_PATH);
}