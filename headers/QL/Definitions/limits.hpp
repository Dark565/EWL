#pragma once

#include "arch.hpp"
#include "int.hpp"

#if defined(__QL__ARCH__x86_64) || defined(__QL__ARCH__AARCH64) || defined(__QL__ARCH__POWERPC64) || defined(__QL__ARCH___MIPS)

#define __QL_MAX_WORD_SIZE 8
#define __QL_MAX_WORD_BITS 64

#elif defined(__QL__ARCH__x86_32) || defined(__QL__ARCH__ARM) || defined(__QL__ARCH__POWERPC)

#define __QL_MAX_WORD_SIZE 4
#define __QL_MAX_WORD_BITS 32

#endif