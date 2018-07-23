#include <winapi.h>

inline void* impl::load(const char* p) {
    return (void*)LoadLibrary(p);
}

inline void impl::free(void* t) {
    FreeLibrary((HMODULE)t);
}

inline void* impl::getFunc(void* t, const char* p) {
    return GetProcAddress((HMODULE)t,p);
}