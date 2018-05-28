#pragma once

#include "../Definitions/defs.hpp"


/*Predefined main for QL initialize*/
int main(int, char**);

#ifdef __QL_LIBRARY_MAIN_REQUIRED

namespace ql {
        #ifdef __QL_LIBRARY_ERRORS_REQUIRED
            void error(std::string);
            #define _ERR_D error
        #else
            #define _ERR_D NULL
        #endif
    /*Valid main for initialize your programs*/

    int main(int, char**);
}

#include "main.inl"

#endif