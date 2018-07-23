#include <dlfcn.h>

inline void* impl::load(const char* p) {
    return dlopen(p,RTLD_LAZY);
}

inline void impl::free(void* t) {
    dlclose(t);
}

inline void* impl::getFunc(void* t, const char* p) {
    return dlsym(t,p);
}