#pragma once

#include <QL/Definitions/Objects/NotCopyable.hpp>
#include <QL/Definitions/int.hpp>

#include <stddef.h>

namespace ql {

    class Thread : NotCopyable {

    protected:

        struct Functor {
            virtual void call() {}
            virtual ~Functor() {}
        };

        template <class T>
        struct EmptyFunctor : Functor {
            T func;

            virtual void call() {
                func();
            }

            EmptyFunctor(T f) : func(f) {}
        };

        template <class T, class A>
        struct ArgumentFunctor : Functor {
            T func;
            A arg;

            virtual void call() {
                func(arg);
            }

            ArgumentFunctor(T f, const A& a) : func(f), arg(a) {}
        };

        template <class C>
        struct ClassFunctor : Functor {

            typedef void(C::*method_t)(void);

            method_t method;
            C* class_c;

            virtual void call() {
                (class_c->method)();
            }

            ClassFunctor(method_t f, C* p) : method(p), class_c(p) {}
        };

        template <class C, class A>
        struct ArgumentClassFunctor : Functor {
            typedef void(C::*method_t)(A);

            method_t method;
            A arg;
            C* class_c;

            virtual void call() {
                (class_c->method)(arg);
            }

            ArgumentClassFunctor(method_t f, const A& a, C* p) : method(f), arg(a), class_c(p) {}

        };

    public:

        typedef uint64_t id_t;
        typedef void*(*thread_func)(void*);

        bool create_c(thread_func,void*);

        template <class T>
        inline bool create(T f) {
            return make_functors(new EmptyFunctor<T>(f));
        }

        template <class T, class A>
        inline bool create(T f, const A& a) {
            return make_functors(new ArgumentFunctor<T,A>(f,a));
        }

        template <class C>
        inline bool create(void(C::*f)(), C* p) {
            return make_functors(new ClassFunctor<C>(f,p));
        }

        template <class C, class A>
        inline bool create(void(C::*f)(A), const A& a, C* p) {
            return make_functors(new ArgumentClassFunctor<C,A>(f,a,p));
        }

        bool isLegit();
        bool kill();
        bool join();
        bool detach();
        bool destroy();
        id_t id();


    protected:

        Functor* d_data;
        id_t p_data;

        bool make_functors(Functor*);
        static void* doThread(void*);


    public:

        ~Thread();
        Thread() : d_data(NULL), p_data(NULL) {}

    };

}