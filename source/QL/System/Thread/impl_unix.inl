#include <QL/System/thread.hpp>

#include <pthread.h>

inline bool impl::join(ql::Thread::id_t th) {
    return !pthread_join((pthread_t)th,NULL);
}

inline bool impl::detach(ql::Thread::id_t th) {
    return !pthread_detach((pthread_t)th);
}

inline bool impl::kill(ql::Thread::id_t th) {
    return !pthread_cancel((pthread_t)th);
}

bool ql::Thread::create_c(ql::Thread::thread_func func, void* arg) {
    destroy();
    return !pthread_create((pthread_t*)&p_data,NULL,func,arg);
}

ql::Thread::id_t ql::Thread::id() {
    return p_data;
}