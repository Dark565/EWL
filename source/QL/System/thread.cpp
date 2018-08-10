#include "QL/System/thread.hpp"

#include <QL/Definitions/defs.hpp>

#include <stddef.h>

#if defined(__QL_OS_UNIX)
    #include "Thread/impl_unix.inl"
#elif defined(__QL_OS_WINDOWS)
    #include "Thread/impl_win32.inl"
//#elif defined(...)
#endif

void* ql::Thread::doThread(void* data) {
    static_cast<ql::Thread::Functor*>(data)->call();
    return NULL;
}

bool ql::Thread::isLegit() {
    return p_data;
}


bool ql::Thread::destroy() {
    kill();
    if(d_data) {
        delete d_data;
        return true;
    }
    return false;
}

bool ql::Thread::make_functors(ql::Thread::Functor* f) {
    bool r = create_c(doThread,(void*)f);
    d_data = f;

    return r;
}

ql::Thread::~Thread() {
    destroy();
}