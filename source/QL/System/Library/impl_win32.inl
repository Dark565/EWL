#include <winapi.h>

bool ql::Library::load(const std::string& p) {
    free();

    if(l_p = (void*)LoadLibrary(p.c_str())) {
        return 1;
    } 
    else {
        return l_p = NULL;
    }
}