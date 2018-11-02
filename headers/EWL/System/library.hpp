#pragma once

#include <string>
#include <EWL/Definitions/Objects/NotCopyable.hpp>
#include <EWL/Definitions/os.hpp>

#if defined(__EWL_OS_UNIX)
    #include "library_unix.inl"
#elif defined(__EWL_OS_WIN32)
    #include "library_win32.inl"
#else
    #error Your target system is not supported by EWL
#endif

namespace ewl {

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

        Library() : l_p(NULL)
        {
            
        }


        static inline std::string toPlatformal(const std::string& s) {
            return s + __EWL_LIBRARY_SUFFIX;
        }
    };

}
