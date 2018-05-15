#pragma once


#define __QL_OS_NOTSUPPORTED

#ifdef __unix__
#define __QL_OS_UNIX

#undef __QL_OS_NOTSUPPORTED
#endif

#ifdef __linux__
#define __QL_OS_LINUX

#undef __QL_OS_NOTSUPPORTED
#endif

#ifdef _WIN32
#define __QL_OS_WINDOWS

#undef __QL_OS_NOTSUPPORTED
#endif

#ifdef __APPLE__
#define __QL_OS_MACOS

#undef __QL_OS_NOTSUPPORTED
#endif

#ifdef __ANDROID__
#define __QL_OS_ANDROID

#undef __QL_OS_NOTSUPPORTED
#endif

#ifdef __FREEBSD__
#define __QL_OS_FREEBSD

#undef __QL_OS_NOTSUPPORTED
#endif