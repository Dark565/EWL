#include "dynamic_lib.hpp"

static ewl::native::librariesStore* t_lib_store = NULL;

ewl::native::librariesStore* ewl::native::getLibrariesStore() {
    if(!t_lib_store) t_lib_store = new ewl::native::librariesStore;
    return t_lib_store;
}

int ewl::native::zeroFunc() {
    return 0;
}