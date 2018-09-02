#pragma once


#define __QL_OS_OTHER 1

#if defined (__unix__)
#define __QL_OS_UNIX 1

#undef __QL_OS_OTHER
#endif

#if defined (__linux__)
#define __QL_OS_LINUX 1

#undef __QL_OS_OTHER
#endif

#if defined (__WIN32__)
#define __QL_OS_WINDOWS 1

#undef __QL_OS_OTHER
#endif

#if defined (__APPLE__)
#define __QL_OS_MACOS 1

#undef __QL_OS_OTHER
#endif

#if defined (__ANDROID__)
#define __QL_OS_ANDROID 1

#undef __QL_OS_OTHER
#endif

#if defined (__FREEBSD__)
#define __QL_OS_FREEBSD 1

#undef __QL_OS_OTHER
#endif