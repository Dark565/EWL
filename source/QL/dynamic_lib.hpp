#pragma once

#include <string>
#include <map>
#include <QL/System/library.hpp>

namespace ql {
    namespace dynamicLib {
        
        std::map<int,ql::Library>* getLibraryHash();

        inline void* loadFunc(int i, const std::string& s)
        {
            return getLibraryHash()->at(i).loadFunc(s);
        }
        
        template <class T>
        inline T loadFunc(int i, const std::string& s)
        {
            return (T)loadFunc(i,s);
        }

        inline ql::Library& getLibrary(int i)
        {
            return getLibraryHash()->at(i);
        }
    }
}