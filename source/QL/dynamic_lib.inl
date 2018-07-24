#include "dynamic_lib.hpp"

static std::map<int,ql::Library>* t_lib_map = NULL;

std::map<int,ql::Library>* ql::dynamicLib::getLibraryHash() {
    if(!t_lib_map) t_lib_map = new std::map<int,ql::Library>;
    return t_lib_map;
}

