#include <QL/System/thread.hpp>

#include <pthread.h>

bool ql::Thread::create_c(ql::Thread::thread_func func, void* arg) {
    destroy();
    return !pthread_create((pthread_t*)&p_data,NULL,func,arg);
}

bool ql::Thread::kill() {
    if(isLegit()) return !pthread_cancel((pthread_t)p_data);
    return false;
}

bool ql::Thread::join() {
    if(isLegit()) return !pthread_join((pthread_t)p_data,NULL);
    return false;
}

bool ql::Thread::detach() {
    if(isLegit()) return !pthread_detach((pthread_t)p_data);
    return false;
}

ql::Thread::id_t ql::Thread::id() {
    return p_data;
}