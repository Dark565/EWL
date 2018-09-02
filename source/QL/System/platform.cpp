#include <QL/System/platform.hpp>
#include <QL/Definitions/os.hpp>

#if defined(__QL_OS_UNIX)
    #include "Platform/impl_unix.inl"
#elif defined(__QL_OS_WINDOWS)
    #include "Platform/impl_win32.inl"
#endif