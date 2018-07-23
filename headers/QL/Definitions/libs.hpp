#pragma once

#if defined(QL_LIB_LINK)
    #define __QL_LIBRARY_LINK
#else
    #define __QL_LIBRARY_LOAD
#endif