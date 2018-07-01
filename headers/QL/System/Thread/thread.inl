#include "thread.hpp"

#include <cstring>

template <class F>
virtual void ql::Thread::FuncThreadCaller<F>::call() {
    func();
}

template <class F, class A>
virtual void ql::Thread::ArgThreadCaller<F,A>::call() {
    func(arg);
}

template <class T, class A>
virtual void ql::Thread::ClassThreadCaller<T,A>::call() {
    (ptr->func)();
}

template <class F>
inline void create(F f) {
    thread_data = new ql::Thread::FuncThreadCaller<F>(f);
    construct();
}

template <class F, class A>
inline void create(F f, A a) {
    thread_data = new ql::Thread::ArgThreadCaller<F,A>(f,a);
    construct();
}

template <class T, class A>
inline void create(T* ptr, A a) {
    thread_data = new ql::Thread::ClassThreadCaller<T,A>(ptr, a);
    construct();
}