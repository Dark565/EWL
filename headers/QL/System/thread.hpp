#pragma once

#include <QL/Definitions/NotCopyable.hpp>

#include <stdlib.h>

namespace ql {

    class Thread : NotCopyable {

        void *d_data, *p_data;

        struct Functor {
            virtual void call();
        };

        template <class T, class Arg>
        struct ArgumentsFunctor : Functor {
            T func;
            Args... args;

            virtual void call() {
                func(args...);
            }

            ArgumentsFunctor(T f, Args&... a) : func(f,a...) {};


        };

        template <class T, class C, class ...Args>
        struct ClassFunctor : ArgumentsFunctor {
            C* object;

            virtual void call() {
                (c->func)(args...);
            }

            ClassFunctor(T f, C* o, Args&... a) : ArgumentsFunctor(f,a), object(o) {};
        };

    public:

        bool destroy();
        bool join();
        bool detach();
        bool kill();
        bool isLegit();

        template <class T, class ...Args>
        void create(T,const Args&...) {
            destroy();

        }

        Thread() : d_data(NULL), p_data(NULL) {}

    };

}