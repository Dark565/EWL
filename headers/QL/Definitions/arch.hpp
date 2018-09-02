#pragma once

#include "compiller.hpp"

#if defined(__amd64__) || defined(__x86_64__)

#define __QL__ARCH__x86_64 1
#define __QL__ARCH__NAME "x86_64"

#elif defined(__i386__)

#define __QL__ARCH__x86_32 1
#define __QL__ARCH__NAME "x86_32"

#elif defined(__arm__)

#define __QL__ARCH__ARM 1
#define __QL__ARCH__NAME "arm"

#elif defined(__aarch64__)

#define __QL__ARCH__AARCH64 1
#define __QL__ARCH__NAME "aarch64"

#elif defined(__powerpc__)

#define __QL__ARCH__POWERPC 1
#define __QL__ARCH__NAME "powerpc"

#elif defined(__powerpc64__)

#define __QL__ARCH__POWERPC64 1
#define __QL__ARCH__NAME "powerpc64"

#elif defined(__mips__)

#define __QL__ARCH__MIPS 1
#define __QL__ARCH__NAME "mips"

#else

#define __QL__ARCH__OTHER 1

#endif

#if defined(__ORDER_LITTLE_ENDIAN__)

#define __QL_ORDER_LITTLE_ENDIAN 1
#define __QL_ORDER_NAME "little-endian"

#elif defined(__ORDER_BIG_ENDIAN__)

#define __QL_ORDER_BIG_ENDIAN 1
#define __QL_ORDER_NAME "big-endian"

#endif

