#pragma once



#ifdef __unix__
#define __QL_UNIX
#endif

#ifdef __linux__
#define __QL_LINUX
#endif

#ifdef _WIN32
#define __QL_WINDOWS
#endif

#ifdef __APPLE__
#define __QL_MACOS
#endif

#ifdef __ANDROID__
#define __QL_ANDROID
#endif