#include "X11.hpp"

namespace impl {

    inline void load_X11_procs(X11_Functions_Set* fs, ql::Library* lib) {
        if(!(fs->r_OpenDisplay       = (X11::OpenDisplay_p)         lib->loadFunction("XOpenDisplay")))
            fs->r_OpenDisplay        = (X11::OpenDisplay_p)         ql::native::zeroFunc;

        if(!(fs->r_CreateWindow      = (X11::CreateWindow_p)        lib->loadFunction("XCreateWindow")))
            fs->r_CreateWindow       = (X11::CreateWindow_p)        ql::native::zeroFunc;
        
        if(!(fs->r_CloseDisplay      = (X11::CloseDisplay_p)        lib->loadFunction("XCloseDisplay")))
            fs->r_CloseDisplay       = (X11::CloseDisplay_p)        ql::native::zeroFunc;

        if(!(fs->r_DefaultRootWindow = (X11::DefaultRootWindow_p)   lib->loadFunction("XDefaultRootWindow")))
            fs->r_DefaultRootWindow  = (X11::DefaultRootWindow_p)   ql::native::zeroFunc;

        if(!(fs->r_GetAtomName       = (X11::GetAtomName_p)         lib->loadFunction("XGetAtomName")))
            fs->r_GetAtomName        = (X11::GetAtomName_p)         ql::native::zeroFunc;

        if(!(fs->r_StoreName         = (X11::StoreName_p)           lib->loadFunction("XStoreName")))
            fs->r_StoreName          = (X11::StoreName_p)           ql::native::zeroFunc;

        if(!(fs->r_Free              = (X11::Free_p)                lib->loadFunction("XFree")))
            fs->r_Free               = (X11::Free_p)                ql::native::zeroFunc;

    }
}

bool G_X11_lib_load() {

    ql::native::libraryData* l_data = ql::native::getLibraryData(ql::native::tags::X11);
    ql::Library* obj = &l_data->object;
    X11_Functions_Set* fs;

    if(!obj->isLegit()) obj->load(__QL_LIB_X11_PATH);

    impl::load_X11_procs(fs,obj);

    if(!l_data->data) {
        l_data->data = new X11_Functions_Set;
        fs = (X11_Functions_Set*) l_data->data;
    }

    return 1;
}

bool G_X11_lib_unload() {

    ql::native::libraryData* l_data = ql::native::getLibraryData(ql::native::tags::X11);
    ql::Library* obj = &l_data->object;

    if(l_data->data) {
        free(l_data->data);
        l_data->data = NULL;
    }

    return obj->free();

}