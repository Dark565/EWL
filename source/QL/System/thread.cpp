#include "QL/System/thread.hpp"

#include <QL/Definitions/os.hpp>

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
        delete d_data; d_data = NULL;
        return true;
    }
    return false;
}

bool ql::Thread::make_functors(ql::Thread::Functor* f) {
    bool r = create_c(doThread,f);
    d_data = f;

    return r;
}

bool ql::Thread::join() {
    if(isLegit()) {
        bool r = _THREAD_join(p_data);
        destroy();
        return r;
    }
    return false;
}

bool ql::Thread::detach() {
    if(isLegit()) {
        return _THREAD_detach(p_data);
    }
    return false;
}

bool ql::Thread::kill() {
    if(isLegit()) {
        return _THREAD_kill(p_data);
    }
    return false;
}

ql::Thread::~Thread() {
    destroy();
}