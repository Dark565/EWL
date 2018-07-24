#pragma once

#include <string>
#include <map>
#include <QL/System/library.hpp>

namespace ql {
    namespace native {
        
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

        inline bool loadLibrary(int i, const std::strign& s)
        {
            ql::Library& lib = getLibrary(i);
            if(!lib.isLegit()) {
                return lib.load(s);
            }
            return true;
        }

        inline bool unloadLibrary(int i)
        {
            return getLibraryHash()->erase(i);
        }
    }
}