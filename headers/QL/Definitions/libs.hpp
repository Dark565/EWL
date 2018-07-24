#pragma once

#define QL_LIB_LOAD

#if defined(QL_LIB_LINK)
    #define __QL_LIBRARY_LINK

#elif defined(QL_LIB_LOAD)
    #define __QL_LIBRARY_LOAD

#endif