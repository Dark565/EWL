#include "EWL/System/thread.hpp"

#include <EWL/Definitions/os.hpp>

#include <stddef.h>

#if defined(__EWL_OS_UNIX)
    #include "Thread/impl_unix.inl"
#elif defined(__EWL_OS_WINDOWS)
    #include "Thread/impl_win32.inl"
//#elif defined(...)
#endif

void* ewl::Thread::doThread(void* data) {
    static_cast<ewl::Thread::Functor*>(data)->call();
    return NULL;
}

bool ewl::Thread::isLegit() {
    return p_data;
}


bool ewl::Thread::destroy() {
    kill();
    if(d_data) {
        delete d_data; d_data = NULL;
        return true;
    }
    return false;
}

bool ewl::Thread::make_functors(ewl::Thread::Functor* f) {
    bool r = create_c(doThread,f);
    d_data = f;

    return r;
}

bool ewl::Thread::join() {
    if(isLegit()) {
        bool r = _THREAD_join(p_data);
        destroy();
        return r;
    }
    return false;
}

bool ewl::Thread::detach() {
    if(isLegit()) {
        return _THREAD_detach(p_data);
    }
    return false;
}

bool ewl::Thread::kill() {
    if(isLegit()) {
        return _THREAD_kill(p_data);
    }
    return false;
}

ewl::Thread::~Thread() {
    destroy();
}
