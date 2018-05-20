#pragma once

#include "../NotCopyable.hpp"
#include "os.hpp"

#include <pthread.h>

namespace ql {
    class Thread : NotCopyable {
    private:
        struct ThreadCaller {
            void* 

            virtual void call();
        };

        /*Function*/

        template <class F> struct FuncThreadCaller : ThreadCaller {
            F func;

            virtual void call();

            FuncThreadCaller(F f) : func(f) {

            }
        };

        /*Function with argument*/
        
        template <class F, class A> struct ArgThreadCaller : ThreadCaller {
            F func;
            A arg;

            virtual void call();

            ArgThreadCaller(F f, A a) : func(f), arg(a) {

            }
        };

        /*Class pointer with a method*/
h
        template <class T, class A> struct ClassTreadCaller : ThreadCaller {
            typedef void(*T::functionClass_t)(A);

            T* ptr;
            F func;
            A arg;

            virtual void call();

            ClassThreadCaller(T* t, functionClass_t f, A arg) : ptr(t), func(f), arg(a) {}

        };

    public:

        Thread() : 
            runned(false)
            thread_data(NULL)
        {}

        /*Build the thread with data*/

        template<class F>           inline void create(F f);
        template<class F, class A>  inline void create(F f, A a);
        template<class T, class F>  inline void create(T* ptr, F f);

        template<class F>           Thread(F f);
        template<class F, class A>  Thread(F f, A a);
        template<class T, class F>  Thread(T* ptr, F f);

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
        bool runned;

        ThreadCaller* thread_data;
        thread::thread_t thread_v;
        
        void construct();
        static int runThread(void* data);
    };

}

#include "thread.inl"