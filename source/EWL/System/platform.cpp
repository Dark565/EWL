#include <EWL/System/platform.hpp>
#include <EWL/Definitions/os.hpp>

#if defined(__EWL_OS_UNIX)
    #include "Platform/impl_unix.inl"
#elif defined(__EWL_OS_WINDOWS)
    #include "Platform/impl_win32.inl"
#endif