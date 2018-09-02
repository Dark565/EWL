#pragma once

#define QL_ATR_PACKED       __attribute__((packed))
#define QL_ATR_CONSTRUCTOR  __attribute__((constructor))
#define QL_ATR_INLINE       __attribute__((always_inline))

#define __QL_STR(x) #x
#define QL_STR(x) __QL_STR(x)

#define __QL_N_TEST_1 ,
#define ______QL_IS_SET(_, x, ...) x
#define ____QL_IS_SET(x) ______QL_IS_SET(x,1,0)
#define __QL_IS_SET(x) ____QL_IS_SET(__QL_N_TEST_##x)
#define QL_IS_SET(x) __QL_IS_SET(x)

#define QL_VAL(x) x