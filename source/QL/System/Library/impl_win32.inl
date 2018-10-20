#include <windows.h>

#define _LIBRARY_load(p)\
    (void*)LoadLibrary(p)

#define _LIBRARY_free(t)\
    FreeLibrary((HMODULE)t)
}

#define _LIBRARY_getFunc(t,p)\
    GetProcAddress((HMODULE)t,p)