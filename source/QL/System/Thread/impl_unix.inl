#include <QL/System/thread.hpp>

#include <pthread.h>

#define _THREAD_join(th) \
    !pthread_join((pthread_t)th,NULL)

#define _THREAD_detach(th) \
    !pthread_detach((pthread_t)th)

#define _THREAD_kill(th) \
    !pthread_cancel((pthread_t)th)

bool ql::Thread::create_c(ql::Thread::thread_func func, void* arg) {
    destroy();
    return !pthread_create((pthread_t*)&p_data,NULL,func,arg);
}

ql::Thread::id_t ql::Thread::id() {
    return p_data;
}