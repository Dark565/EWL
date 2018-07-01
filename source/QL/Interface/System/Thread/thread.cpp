#include <QL/System/Thread/thread.hpp>

#include <QL/Definitions/defs.hpp>

#if defined(__QL_OS_UNIX)
    #include "PosixThread/construct.inl"
#elif defined(__QL_OS_WINDOWS)
    #include "Win32/construct.inl"
#endif