#pragma once

#define QL_ATR_PACKED       __attribute__((packed))
#define QL_ATR_CONSTRUCTOR  __attribute__((constructor))
#define QL_ATR_INLINE       __attribute__((always_inline))

#define __EWL_STR(x) #x
#define QL_STR(x) __EWL_STR(x)

#define __EWL_N_TEST_1 ,
#define ______EWL_IS_SET(_, x, ...) x
#define ____EWL_IS_SET(x) ______EWL_IS_SET(x,1,0)
#define __EWL_IS_SET(x) ____EWL_IS_SET(__EWL_N_TEST_##x)
#define QL_IS_SET(x) __EWL_IS_SET(x)

#define QL_VAL(x) x