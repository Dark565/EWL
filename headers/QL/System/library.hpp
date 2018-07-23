#pragma once

#include <string>
#include <QL/Definitions/NotCopyable.hpp>
#include <QL/Definitions/defs.hpp>

#if defined(__QL_OS_UNIX)
    #include "library_unix.inl"
#elif defined(__QL_OS_WIN32)
    #include "library_win32.inl"
#else
    #error Your target system is not supported by Qer Library
#endif

namespace ql {

    class Library : NotCopyable {
        void* l_p;
    public:
        void* loadFunction(const std::string&);

        template <class T>
        T loadFunction(const std::string& s)
        {
            return (T)loadFunction(s);
        }

        bool load(const std::string&);
        bool free();

        bool isLegit();

        inline Library(const std::string& str) : l_p(NULL)
        {
            load(str);
        }

        inline ~Library()
        {
            free();
        }

        Library() = default;


        static inline std::string toPlatformal(const std::string& s) {
            return s + __QL_LIBRARY_SUFFIX;
        }
    };

}