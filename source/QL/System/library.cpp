#include <QL/System/library.hpp>
#include <QL/Definitions/defs.hpp>

#include <string.h>

namespace impl {
    inline void* load(const char*);
    inline void free(void*);
    inline void* getFunc(void*,const char*);
}

#if defined(__QL_OS_UNIX)
    #include "Library/impl_unix.inl"
#elif defined(__QL_OS_WIN32)
    #include "Library/impl_win32.inl"
#else
    #error Your target system is not supported by Qer Library
#endif

bool ql::Library::load(const std::string& p) {
    free();

    if(l_p = impl::load(p.c_str())) {
        return 1;
    }
    else {
        return l_p = NULL;
    }
}

bool ql::Library::free() {
    if(isLegit()) {
        impl::free(l_p);
        l_p = NULL;
    }
}

bool ql::Library::isLegit() {
    return l_p;
}

void* ql::Library::loadFunction(const std::string& p) {
    if(isLegit()) {
        return impl::getFunc(l_p,p.c_str());
    }
    return NULL;
}