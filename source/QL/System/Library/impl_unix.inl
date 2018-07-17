#include <dlfcn.h>

inline void* lib::load(const char* p) {
    return dlopen(p,RTLD_LAZY);
}

inline void lib::free(void* t) {
    dlclose(t);
}

inline void* lib::getFunc(void* t, const char* p) {
    return dlsym(t,p);
}