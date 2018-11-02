#pragma once

#include "arch.hpp"
#include "int.hpp"

#if defined(__EWL__ARCH__x86_64) || defined(__EWL__ARCH__AARCH64) || defined(__EWL__ARCH__POWERPC64) || defined(__EWL__ARCH___MIPS)

#define __EWL_MAX_WORD_SIZE 8
#define __EWL_MAX_WORD_BITS 64

#elif defined(__EWL__ARCH__x86_32) || defined(__EWL__ARCH__ARM) || defined(__EWL__ARCH__POWERPC)

#define __EWL_MAX_WORD_SIZE 4
#define __EWL_MAX_WORD_BITS 32

#endif