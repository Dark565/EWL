#pragma once

#include <string>
#include <QL/Definitions/NotCopyable.hpp>

namespace ql {

    class Library : NotCopyable {
        void* l_p;
    public:
        void* loadFunction(const std::string&);

        bool loadLibrary(const std::string&);
        bool freeLibrary();

        bool isLegit();

        inline Library(const std::string& str) 
        {
            loadLibrary(str);
        }

        inline ~Library()
        {
            freeLibrary();
        }

        Library() = default;
    };

}