#include <dlfcn.h>

#define _LIBRARY_load(p)\
    dlopen(p,RTLD_LAZY)

#define _LIBRARY_free(t)\
    dlclose(t)

#define _LIBRARY_getFunc(t,p)\
    dlsym(t,p)