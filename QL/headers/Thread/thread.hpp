#pragma once

#include <NotCopyable.hpp>

#include <pthread.h>

namespace ql {
    class Thread : NotCopyable {
    private:
        struct ThreadCaller {
            virtual void call();
        };

        /*Function with argument*/
        
        template struct <class F, class A> ArgThreadCaller : ThreadCaller {
            F func;
            A arg;

            virtual void call();

            ArgThreadCaller(F f, A a) : func(f), arg(a) {}
        };

        /*Class pointer with a method*/

        template struct <class T, class T::F> ClassThreadCaller : ThreadCaller {
            T* ptr;
            F func;

            virtual void call();

            ClassThreadCaller(T* t, F f) : ptr(t), func(f) {}
        };

        /*Class pointer with a method and an argument*/

        template struct <class T, class T::F, class A> ClassArgThreadCaller : ThreadCaller {
            T* ptr;
            F func;
            A arg;

            virtual void call();

            ClassArgThreadCaller(T* t, F f, A a) : ptr(t), func(f), arg(a) {}
        };

    public:

        /*Build the thread with data*/

        template<class F, class A>              void create(F* f, A a);
        template<class T, class T::F>           void create(T* ptr, F* func);
        template<class T, class T::F, class A>  void create(T* ptr, F* func, A arg);

        /*Joins the thread*/

        void join();

        /*Detaches the thread*/

        void detach();

        /*Checks is thread joinable*/

        bool isLegit();
        #define joinable isLegit

        /*Checks is thread in work*/

        bool isWorking();

        /*Stops a thread*/

        void stop();

        /*Destroys a currently working thread*/

        void destroy();

    private:
        ThreadCaller* thread_data;
        pthread_t thread_v;

        static int runThread(void* data);
    };

}