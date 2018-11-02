#include <EWL/System/library.hpp>
#include <EWL/Definitions/os.hpp>

#include <string.h>

#if defined(__EWL_OS_UNIX)
    #include "Library/impl_unix.inl"
#elif defined(__EWL_OS_WIN32)
    #include "Library/impl_win32.inl"
#else
    #error Your target system is not supported by Qer Library
#endif

bool ewl::Library::load(const std::string& p) {
    free();

    return l_p = _LIBRARY_load(p.c_str());
}

bool ewl::Library::free() {
    if(isLegit()) {
        _LIBRARY_free(l_p);
        l_p = NULL;
        return true;
    }
    return false;
}

bool ewl::Library::isLegit() {
    return l_p;
}

void* ewl::Library::loadFunction(const std::string& p) {
    if(isLegit()) {
        return _LIBRARY_getFunc(l_p,p.c_str());
    }
    return NULL;
}