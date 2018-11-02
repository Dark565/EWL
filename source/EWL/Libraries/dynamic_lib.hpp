#pragma once

#include <string>
#include <EWL/System/library.hpp>

namespace ewl {
    namespace native {

         enum tags {
            X11,
            Xrandr,

            count
        };

        struct libraryData {
            void* data;
            ewl::Library object;
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

        inline ewl::Library& getLibrary(int i)
        {
            return getLibraryData(i)->object;
        }

        inline bool loadLibrary(int i, const std::string& s)
        {
            ewl::Library& lib = getLibrary(i);
            if(!lib.isLegit()) {
                return lib.load(s);
            }
            return true;
        }

        inline bool unloadLibrary(int i)
        {
            ewl::Library& lib = getLibrary(i);
            return lib.free();
        }
    }
}