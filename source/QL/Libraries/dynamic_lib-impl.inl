#include "dynamic_lib.hpp"

static ql::native::librariesStore* t_lib_store = NULL;

ql::native::librariesStore* ql::native::getLibrariesStore() {
    if(!t_lib_store) t_lib_store = new ql::native::librariesStore;
    return t_lib_store;
}

int ql::native::zeroFunc() {
    return 0;
}