#pragma once

#include <string>
#include <QL/System/library.hpp>

namespace ql {
    namespace native {

         enum tags {
            X11,
            Xrandr,

            count
        };

        struct libraryData {
            void* data;
            ql::Library object;
        };

        struct librariesStore {
            libraryData library[tags::count]; 
        };

        int zeroFunc();
        
        librariesStore* getLibrariesStore();

        inline libraryData* getLibraryData(int i)
        {
            return &getLibrariesStore()->library[i];
        }

        inline void* loadFunc(int i, const std::string& s)
        {
            return getLibraryData(i)->object.loadFunction(s);
        }
        
        template <class T>
        inline T loadFunc(int i, const std::string& s)
        {
            return (T)loadFunc(i,s);
        }

        inline ql::Library& getLibrary(int i)
        {
            return getLibraryData(i)->object;
        }

        inline bool loadLibrary(int i, const std::string& s)
        {
            ql::Library& lib = getLibrary(i);
            if(!lib.isLegit()) {
                return lib.load(s);
            }
            return true;
        }

        inline bool unloadLibrary(int i)
        {
            ql::Library& lib = getLibrary(i);
            return lib.free();
        }
    }
}