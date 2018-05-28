#include <Thread/thread.hpp>

#include <pthread.h>

void ql::Thread::construct() {
    destroy();
    pthread_create(&thread_v,NULL,&ql::Thread::runThread,(void*)thread_data);
}

void ql::Thread::detach() {
    pthread_detach(thread_v);
}

void ql::Thread::join() {
    pthread_join(thread_v);
}